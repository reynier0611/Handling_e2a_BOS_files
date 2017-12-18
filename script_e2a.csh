#!/bin/csh -f

#Bos Files
mkdir bosfiles
mv bos_*_v1.A00 bosfiles

echo "Listing BOS Files..."
ls bosfiles

./WriteRootDst -o clas_out.root bosfiles/*

#CLASTOOL ROOT Files
mkdir rootfiles
mv *.root* rootfiles

echo "Listing ROOT Files..."
ls rootfiles

./write_tree_e2a rootfiles/*.root*
