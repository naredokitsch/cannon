#!/bin/bash

tres=3
zero=0
numberOfVertices=$(grep "v " $1 | wc -l); 
fichier=$(echo $1 | cut -d. -f1)

vertex=( $(cat $1 | grep "v " | sed 's/v */{/g' | sed 's/$/}/g') )
n_vertex=( $(cat $1 | grep "vn " | sed 's/vn */{/g' | sed 's/$/}/g') )
t_vertex=( $(cat $1 | grep -Eo "^vt *-?[0-9]*.?[0-9]* *-?[0-9]*.?[0-9]*" | sed 's/vt */{/g' | sed 's/$/}/g') )

quads=( $(cat $1 | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){4} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )
trng=( $(cat $1 | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){3} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )
poly=( $(cat $1 | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){5,} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )


# Use Parameter Expansion:
quads=("${quads[@]/%/}}")
trng=("${trng[@]/%/}}")
poly=("${poly[@]/%/}}")

if [ $numberOfVertices -eq $(( ${#vertex[@]} / tres)) ]; then
	echo "vertex checked!"

	echo "#include <vector>" > $fichier.cpp
	echo "" >> $fichier.cpp
	echo "using namespace std;" >> $fichier.cpp
	echo "" >> $fichier.cpp

	echo "std::vector< std::vector<float> >" coord_$fichier { $(echo ${vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo vertices = $((${#vertex[@]} / 3))

	echo "std::vector< std::vector<float> >" text_$fichier { $(echo ${t_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo texturas = $((${#t_vertex[@]} / 2))

	echo "std::vector< std::vector<float> >" normals_$fichier { $(echo ${n_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo normales = $((${#n_vertex[@]} / 3))

	echo "std::vector< std::vector< std::vector<int> > >" quads_$fichier "{{"$(echo ${quads[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo cuadrilateros = ${#quads[@]}

	echo "std::vector< std::vector< std::vector<int> > >" trng_$fichier "{{"$(echo ${trng[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo triangulos = ${#trng[@]}

	echo "std::vector< std::vector< std::vector<int> > >" poly_$fichier "{{"$(echo ${poly[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo poligonos = ${#poly[@]}
fi


