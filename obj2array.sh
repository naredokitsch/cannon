#!/bin/bash

tres=3
dos=dos
zero=0
numberOfVertices=$(grep "v " $1 | wc -l); 
fichier=$(echo $1 | cut -d. -f1)

# Se recorren los indices
awk '/^f/ {for(i=2; i<=NF; i++) {split($i,point,"/"); $i=point[1]-1"/"point[2]-1"/"point[3]-1} print}' $1 > faces.txt
sed -ie 's/-1\/-1\/-1//g' faces.txt
echo faces created.

vertex=( $(cat $1 | grep "v " | sed 's/v */{/g' | sed 's/$/}/g') )
n_vertex=( $(cat $1 | grep "vn " | sed 's/vn */{/g' | sed 's/$/}/g') )
t_vertex=( $(cat $1 | grep -Eo "^vt *-?[0-9]*.?[0-9]* *-?[0-9]*.?[0-9]*" | sed 's/vt */{/g' | sed 's/$/}/g') )

quads=( $(cat faces.txt | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){4} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )
trng=( $(cat faces.txt | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){3} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )
poly=( $(cat faces.txt | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){5,} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )


# Use Parameter Expansion:
quads=("${quads[@]/%/}}")
trng=("${trng[@]/%/}}")
poly=("${poly[@]/%/}}")

if [ $numberOfVertices -eq $(( ${#vertex[@]} / tres)) ]; then
	echo "vertex checked!"

	echo "#include <vector>" > $fichier.cpp
	echo "#include <map>" >> $fichier.cpp
	echo "" >> $fichier.cpp
	echo "using namespace std;" >> $fichier.cpp
	echo "" >> $fichier.cpp

	echo "vector<vector<float> >" vertex_$fichier "{"$(echo ${vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo vertices = $((${#vertex[@]} / 3))

	echo "vector<vector<float> >" texts_$fichier "{"$(echo ${t_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo texturas = $((${#t_vertex[@]} / 2))

	echo "vector<vector<float> >" normals_$fichier "{"$(echo ${n_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo normales = $((${#n_vertex[@]} / 3))

	echo "vector<vector<vector<int> > >" quads_$fichier "{{"$(echo ${quads[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo cuadrilateros = ${#quads[@]}

	echo "vector<vector<vector<int> > >" trng_$fichier "{{"$(echo ${trng[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo triangulos = ${#trng[@]}

	echo "vector<vector<vector<int> > >" poly_$fichier "{{"$(echo ${poly[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n')"};" >> $fichier.cpp
	echo poligonos = ${#poly[@]}

	echo "" >> $fichier.cpp
	echo "map<string,vector<vector<float> > > geo_"$fichier" = {{\"vertex\", "vertex_$fichier"},{\"texts\", "texts_$fichier"},{\"normals\", "normals_$fichier"}};" >> $fichier.cpp
	echo "map<string,vector<vector<vector<int> > > > faces_"$fichier" = {{\"quads\", "quads_$fichier"},{\"trng\", "trng_$fichier"},{\"poly\", "poly_$fichier"}};" >> $fichier.cpp

fi
