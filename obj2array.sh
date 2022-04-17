#!/bin/bash

tres=3
zero=0
numberOfVertices=$(grep "v " $1 | wc -l); 
fichier=$(echo $1 | cut -d. -f1)

# coord_canhao = 20694
# t_vertex_canhao = 16662
# n_vertex_canhao = 13584
# quads_canhao = 52137
# trng_canhao = 3132

vertex=( $(cat $1 | grep "v " | sed 's/v */{/g' | sed 's/$/}/g') )
n_vertex=( $(cat $1 | grep "vn " | sed 's/vn *//g') )
t_vertex=( $(cat $1 | grep -Eo "^vt *-?[0-9]*.?[0-9]* *-?[0-9]*.?[0-9]*" | sed 's/vt *//g') )
quads=( $(cat $1 | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){4} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )
trng=( $(cat $1 | sed 's/\/\//\/0\//g' | grep -oE "^f( *-?[0-9]*/-?[0-9]*/-?[0-9]*){3} *.?$" | sed 's/f */{/g' | sed 's/[^0-9]*$//g' | sed 's/ /\}\,\{/g' | sed 's/\//,/g' | sed 's/$/\}/g') )


# Use Parameter Expansion:
 quads=("${quads[@]/%/}}")
 tgrng=("${trng[@]/%/}}")

if [ $numberOfVertices -eq $(( ${#vertex[@]} / tres)) ]; then
	echo "vertex checked!"

	echo "std::vector< std::vector<float> >" coord_$fichier { $(echo ${vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" > $fichier.cpp
	echo vertices = $((${#vertex[@]} / 3))

	# echo float t_vertex_$fichier [] = { {$(echo ${#t_vertex[@]} ${t_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	# echo t_vertex_$fichier = ${#t_vertex[@]}

	# echo float n_vertex_$fichier [] = { $(echo ${#n_vertex[@]} ${n_vertex[@]} | sed 's/ / , /g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	# echo n_vertex_$fichier = ${#n_vertex[@]}

	echo "std::vector< std::vector< std::vector<int> > >" quads_$fichier "{{"$(echo ${quads[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo cuadrilateros = ${#quads[@]}

	echo "std::vector< std::vector< std::vector<int> > >" trng_$fichier "{{"$(echo ${trng[@]} | sed 's/ /\}\,\{/g' | tr -d '\r' | tr -d '\n') "} ;" >> $fichier.cpp
	echo triangulos = ${#trng[@]}
fi


