#!/bin/bash -E

# Változók:
#  Biztos:
#   NAME - A feladat fájlneve
#  Bizonytalan:
#   ID - Feladat ID és útvonal mesteren
#   katid
#   temid
#   felid
#   szintn - Szint hosszú neve
#   teman - Téma hosszú neve
#   feln - Feladat hosszú neve

if [ -z "$ID" -a $# -eq 3 ]; then
    export ID="$*"
elif [ -z "$ID" -a $# -eq 1 ]; then
    {
        IFS=$'\n'
        select feladatpdf in $(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/files.list | grep -P "/($1)(?: \\*+)?/feladat.pdf\$"); do
            for temline in $(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/temak.tsv); do
                temid="$(echo "$temline" | cut -d$'\t' -f1)"
                szint="$(echo "$temline" | cut -d$'\t' -f2)"
                teman="$(echo "$temline" | cut -d$'\t' -f3)"
                [ "${feladatpdf:0:${#teman}}" == "$teman" ] || continue

                for felline in $(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/"$teman"/flist.tsv); do
                    felid="$(echo "$felline" | cut -d$'\t' -f1)"
                    feln="$(echo "$felline" | cut -d$'\t' -f2)"
                    nehezseg="$(echo "$felline" | cut -d$'\t' -f3)"
                    [ "$feladatpdf" == "$teman/$feln/feladat.pdf" ] || continue

                    export ID="$temid $felid"
                    break 3
                done
            done
            echo -e "\033[41m Failed to lookup ID for \033[1m$feladatpdf\033[0m"
        done
    }
elif [ -z "$ID" -a $# -eq 0 ]; then
    {
        IFS=$'\n'
        temlist="$(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/temak.tsv | tail +2)"
        while :; do
            temid="$(dialog --stdout --title "Feladatválasztás" --menu "Kérjük, válasszon témát:" 50 75 50 \
                "" "Folytatás mester nélkül" \
                $(for temline in $temlist; do
                    temid="$(echo "$temline" | cut -d$'\t' -f1)"
                    szint="$(echo "$temline" | cut -d$'\t' -f2)"
                    teman="$(echo "$temline" | cut -d$'\t' -f3)"
                    
                    echo "$temid"
                    echo "$szint / $teman"
                done)
            )"
            if [ -z "$temid" ]; then
                break
            fi

            temline=$(echo "$temlist" | grep "^$temid"$'\t')
            temid="$(echo "$temline" | cut -d$'\t' -f1)"
            szint="$(echo "$temline" | cut -d$'\t' -f2)"
            teman="$(echo "$temline" | cut -d$'\t' -f3)"

            ID="$(dialog --stdout --title "Feladatválasztás" --menu "Kérjük, válasszon feladatot:" 50 75 50 \
                "" "Vissza" \
                $(for felline in $(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/"$teman"/flist.tsv | tail +2); do
                    felid="$(echo "$felline" | cut -d$'\t' -f1)"
                    feln="$(echo "$felline" | cut -d$'\t' -f2)"
                    nehezseg="$(echo "$felline" | cut -d$'\t' -f3)"

                    echo "$temid $felid"
                    echo "$feln"
                done)
            )"

            if [ -n "$ID" ]; then
                export ID
                break
            fi
        done
    }
elif [ $# -gt 0 ]; then
    echo "Usage: $0 [kat tem fel | 'feladatnév-regex']"
fi

if [ -n "$ID" ]; then
    export katid="$(echo "$ID" | cut -d' ' -f1)"
    export temid="$(echo "$ID" | cut -d' ' -f2)"
    export felid="$(echo "$ID" | cut -d' ' -f3)"

    temline="$(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/temak.tsv | grep "^$katid $temid"$'\t')"
    echo "Téma: $temline"
    export szintn="$(echo "$temline" | cut -d$'\t' -f2)"
    export teman="$(echo "$temline" | cut -d$'\t' -f3)"

    felline="$(wget -qO- https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/"$teman"/flist.tsv | grep "^$felid"$'\t')"
    echo "Feladat: $felline"
    export feln="$(echo "$felline" | cut -d$'\t' -f2)"
else
    echo -e "\033[41mNem található mester-es feladat.\033[0m"
fi

if [ -z "$NAME" ]; then
    read -p "Feladat fájlneve: " NAME
fi
echo "$NAME" | grep -P '^[a-zA-Z0-9:._-]+$' >/dev/null || { echo "Invalid name"; exit 2; }
if [ -e "$NAME".cpp ]; then
    echo "Ilyen már létezik!"
    exit 3
fi

cd "$(dirname "$0")"

cp lib.cpp "$NAME".cpp
touch "$NAME".txt
sed -i~ 's#^PROJECTS = \(.*\) ;$#PROJECTS = \1 '"$NAME"' ;#' Jamfile
echo "$NAME" >>.gitignore

if [ -n "$teman" -a -n "$feln" ]; then
    sed -i~ 's#^// Feladat:#& '"$szintn / $teman / $feln"'#' "$NAME".cpp
    wget https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/"$teman"/"$feln"/minta.zip -O"$NAME".zip \
        && unzip -p "$NAME".zip be1.txt >"$NAME".txt \
        || true
    firefox https://raw.githubusercontent.com/lezsakdomi/elte-mester-data/master/"$teman"/"$feln"/feladat.pdf || true
fi

if [ ! -s "$NAME".txt ]; then
    vim "$NAME".txt || exit $?
fi
vim "$NAME".cpp || exit $?
