
### argv: dataset Lepflavor ID era isotrig allpt



for isotrig in 1
do
	for allpt in 0 1
	do
# 		./FakeRate_2017data.o Data El MVA2017TightV2RC 2017B ${isotrig} ${allpt} &
# 		./FakeRate_2017data.o Data El MVA2017TightV2RC 2017C ${isotrig} ${allpt} &
# 		./FakeRate_2017data.o Data El MVA2017TightV2RC 2017D ${isotrig} ${allpt} &
# 		./FakeRate_2017data.o Data El MVA2017TightV2RC 2017E ${isotrig} ${allpt} &
# 		./FakeRate_2017data.o Data El MVA2017TightV2RC 2017F ${isotrig} ${allpt} 

		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017B ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017C ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017D ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017E ${isotrig} ${allpt} &
		# ./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_1 ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_2_1 ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_2_2 ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_2_3 ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_2_4 ${isotrig} ${allpt} &
		./FakeRate_2017data.o Data Muons CBTightMiniIso 2017F_2_5 ${isotrig} ${allpt} 
		done
done


echo "DONE"
