#!/bin/bash
# g++ run.cpp -Wall -std=c++11 -O3 sfmt/SFMT.c  -o run


xpArray=("graph_spa_500_0_xp" "graph_spa_500_10_xp")
tpArray=("graph_spa_500_0_tp" "graph_spa_500_10_tp")
thpArray=("graph_spa_500_0_thp" "graph_spa_500_10_thp")
hpArray=("graph_spa_500_0_hp" "graph_spa_500_10_hp")
npArray=("graph_spa_500_0_np" "graph_spa_500_10_np")
idpArray=("graph_spa_500_0_idp" "graph_spa_500_10_idp")
lostArray=("graph_spa_500_10_tp" "graph_spa_500_0_idp" "graph_spa_500_10_idp")
spa10=("graph_spa_500_10_xp" "graph_spa_500_10_tp" "graph_spa_500_10_thp" "graph_spa_500_10_hp" "graph_spa_500_10_np" "graph_spa_500_10_idp")
spa10_t=("graph_spa_500_10_xp" "graph_spa_500_10_tp" "graph_spa_500_10_thp")
spa10_h=("graph_spa_500_10_hp" "graph_spa_500_10_np" "graph_spa_500_10_idp")

# ./run lRR 251 10000 0.02 graph_spa_500_0_xp 10000 0.1 10 lt sum

# for str in ${xpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
# done

# for str in ${xpArray[@]}; do
#   echo $str
#   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run lRR 261 1000 0.02 $str 1000 0.1 10 lt sum
# done

# ./run greedy 151 1000 0.02 graph_spa_500_10_xp 1000 0.1 10 lt sum


# for str in ${tpArray[@]}; do
#   echo $str
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${tpArray[@]}; do
#     ./run lRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# done


# for str in ${tpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
# done

# for str in ${tpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run lRR 151 1000 0.02 $str 1000 0.1 10 lt sum
# done
# ./run greedy 151 1000 0.02 graph_spa_500_10_tp 1000 0.1 10 lt sum

# for str in ${thpArray[@]}; do
#   echo $str
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${thpArray[@]}; do
#     ./run lRR 151 10000 0.02 $str 10000 0.1 10 lt sum
# done
# ./run greedy 151 1000 0.02 graph_spa_500_10_thp 1000 0.1 10 lt sum



# for str in ${thpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
# done

# for str in ${thpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 lt sum
# done


# for str in ${hpArray[@]}; do
#   echo $str
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${hpArray[@]}; do
#     ./run lRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# done


# for str in ${hpArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sumf
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done


# for str in ${hpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run lRR 251 1000 0.02 $str 1000 0.1 10 lt sum
# done

# for str in ${idpArray[@]}; do
#   echo $str
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${idpArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
# done

# for str in ${idpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run lRR 251 1000 0.02 $str 1000 0.1 10 lt sum
# done

# for str in ${idpArray[@]}; do
#   echo $str
#   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic min
#   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic min
#   ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic min
#   ./run supers 261 10000 0.02 $str 10000 0.1 10 ic min
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic min
#   ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic min
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic min
# done


# for str in ${idpArray[@]}; do
#   echo $str
#   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt min
#   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt min
#   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt min
#   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt min
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt min
#   ./run lRR 251 10000 0.02 $str 10000 0.1 10 lt min
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt min
# done


# for str in ${npArray[@]}; do
#   echo $str
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 251 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${npArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${npArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run myopic 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supers 261 10000 0.02 $str 10000 0.1 10 lt sum
# #   ./run supert 261 10000 0.02 $str 10000 0.1 10 lt sum
#   ./run lRR 251 1000 0.02 $str 10000 0.1 10 lt sum
# done

# for str in ${spa10_h[@]}; do
#   ./run greedy 81 10000 0.02 $str 10000 0.1 10 ic sum
# done

for str in ${spa10_t[@]}; do
  ./run greedy 151 10000 0.02 $str 10000 0.1 10 ic sum
done

# for str in ${spa10_h[@]}; do
#   ./run lRR 151 1000 0.02 $str 10000 0.1 10 lt sum
#   ./run greedy 151 10000 0.02 $str 10000 0.1 10 lt sum
# done

# ./run lRR 151 1000 0.02 graph_spa_500_10_hp 10000 0.1 10 lt sum
# ./run lRR 151 1000 0.02 graph_spa_500_10_idp 10000 0.1 10 lt sum
# ./run greedy 151 10000 0.02 graph_spa_500_10_idp 10000 0.1 10 lt sum
# ./run lRR 151 10000 0.02 graph_spa_500_10_np 10000 0.1 10 lt sum


methodsArray=("sRR" "tRR" "myopic")
lRRArray=("lRR")
gdArray=("greedy")
superArray=("supers" "supert")

# for str in ${tpArray[@]}; do
#     ./run myopic 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run sRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run tRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run supers 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run supert 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run lRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run greedy 311 1000 0.02 $str 1000 0.1 10 ic min
# done

# for str in ${thpArray[@]}; do
#     ./run myopic 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run sRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run tRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run supers 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run supert 321 1000 0.02 $str 1000 0.1 10 ic min
#     ./run lRR 311 1000 0.02 $str 1000 0.1 10 ic min
#     ./run greedy 311 1000 0.02 $str 1000 0.1 10 ic min
# done


# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 201 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 201 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 201 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 201 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_thp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_thp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_thp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# done


# for str in ${lRRArray[@]}; do
#     echo $str
#     ./run $str 101 400 0.01 soc-sign-bitcoinalpha_tp 400 0.1 10 ic sum
#     ./run $str 101 400 0.01 soc-sign-bitcoinotc_tp 400 0.1 10 ic sum
#     ./run $str 91 400 0.01 facebook_combined_tp 400 0.1 10 ic sum
#     ./run $str 91 400 0.01 twitter_combined_tp 400 0.1 10 ic sum
# done

# for str in ${greedy[@]}; do
#     echo $str
#     ./run $str 51 400 0.01 soc-sign-bitcoinalpha_tp 400 0.1 10 ic sum
#     ./run $str 51 400 0.01 soc-sign-bitcoinotc_tp 400 0.1 10 ic sum
# done

# for str in ${lRRArray[@]}; do
#     echo $str
#     ./run $str 101 400 0.01 soc-sign-bitcoinalpha_thp 400 0.1 10 lt sum
#     ./run $str 101 400 0.01 soc-sign-bitcoinotc_thp 400 0.1 10 lt sum
#     ./run $str 91 400 0.01 facebook_combined_thp 400 0.1 10 lt sum
#     ./run $str 91 400 0.01 twitter_combined_thp 400 0.1 10 lt sum
# done

# for str in ${superArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# # for str in ${superArray[@]}; do
# #     echo $str
# #     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_thp 4000 0.1 10 ic sum
# #     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_thp 4000 0.1 10 ic sum
# #     ./run $str 91 4000 0.01 facebook_combined_thp 4000 0.1 10 ic sum
# #     # ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# # done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 91 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${superArray[@]}; do
#     echo $str
#     ./run $str 91 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# done

# for str in ${superArray[@]}; do
#     echo $str
#     ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# done

# for str in ${xpArray[@]}; do
#   echo $str
#   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run lRR 261 1000 0.02 $str 1000 0.1 10 ic sum
# done

# for str in ${xpArray[@]}; do
#   echo $str
#   echo $str
# done


samplethp=("spa0_thp_sample_50" "spa0_thp_sample_100" "spa0_thp_sample_150" "spa0_thp_sample_200" "spa0_thp_sample_250" "spa0_thp_sample_300" "spa0_thp_sample_350" "spa0_thp_sample_400" "spa0_thp_sample_450")

sampletp=("spa0_tp_sample_50" "spa0_tp_sample_100" "spa0_tp_sample_150" "spa0_tp_sample_200" "spa0_tp_sample_250" "spa0_tp_sample_300" "spa0_tp_sample_350" "spa0_tp_sample_400" "spa0_tp_sample_450")


# for i in "${!sampletp[@]}"; do
#     budget=$(((i+1) * 30 + 1))
#     budget_my=$(((i+1) * 30 + 11))

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run greedy ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run greedy ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min
    
#     # echo "${budget} ${budget_my} ${sampletp[$i]}"
#     # ./run sRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${sampletp[$i]}"
#     # ./run tRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${sampletp[$i]}"
#     # ./run myopic ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${sampletp[$i]}"
#     # ./run supers ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${sampletp[$i]}"
#     # ./run supert ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

# done



 
# ./run lRR 210 1000 0.02 spa0_tp_sample_350 1000 0.1 10 ic min
# ./run lRR 270 1000 0.02 spa0_tp_sample_450 1000 0.1 10 ic min


# for i in "${!sampletp[@]}"; do
#     budget=$(((i+1) * 30 + 1))
#     budget_my=$(((i+1) * 30 + 11))
#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run sRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run tRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run myopic ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run supers ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run supert ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run lRR ${budget} 1000 0.02 ${sampletp[$i]} 1000 0.1 10 lt min
# done



# for i in "${!samplethp[@]}"; do
#     budget=$(((i+1) * 30 + 1))
#     budget_my=$(((i+1) * 30 + 11))

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run greedy ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 ic min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run greedy ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run sRR ${budget} 10000 0.02 ${samplethp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run tRR ${budget} 10000 0.02 ${samplethp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run myopic ${budget_my} 10000 0.02 ${samplethp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run supers ${budget_my} 10000 0.02 ${samplethp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run supert ${budget_my} 10000 0.02 ${samplethp[$i]} 10000 0.1 10 ic min

#     # echo "${budget} ${budget_my} ${samplethp[$i]}"
#     # ./run lRR ${budget} 1000 0.02 ${samplethp[$i]} 1000 0.1 10 ic min
# done


# for i in "${!samplethp[@]}"; do
#     budget=$(((i+1) * 30 + 1))
#     budget_my=$(((i+1) * 30 + 11))
#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run sRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run tRR ${budget} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run myopic ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run supers ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run supert ${budget_my} 10000 0.02 ${sampletp[$i]} 10000 0.1 10 lt min

#     echo "${budget} ${budget_my} ${sampletp[$i]}"
#     ./run lRR ${budget} 1000 0.02 ${sampletp[$i]} 1000 0.1 10 lt min
# done

