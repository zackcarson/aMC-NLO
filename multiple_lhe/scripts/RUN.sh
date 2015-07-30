start=`date +%s`

root -b -q -l multiple_lhe.C < events_100k.sh
root -b -q -l multiple_lhe.C < events_50k.sh

hadd tree.root ../output/tree_100k_1.root ../output/tree_100k_2.root ../output/tree_100k_3.root ../output/tree_100k_4.root ../output/tree_50k_1.root ../output/tree_50k_2.root ../output/tree_50k_3.root ../output/tree_50k_4.root ../output/tree_50k_5.root

rm ../output/tree_*

root -l lheplot.C

mv *.pdf ../output

end=`date +%s`

echo Congratulations! Job Complete.  Total Time Elapsed: $((end-start)) seconds.
