#!/bin/bash
# g++ run.cpp -Wall -std=c++11 -O3 sfmt/SFMT.c  -o run


xpArray=("graph_spa_500_0_xp" "graph_spa_500_10_xp")
tpArray=("graph_spa_500_0_tp" "graph_spa_500_10_tp")
thpArray=("graph_spa_500_0_thp" "graph_spa_500_10_thp")
hpArray=("graph_spa_500_0_hp" "graph_spa_500_10_hp")
npArray=("graph_spa_500_0_np" "graph_spa_500_10_np")
idpArray=("graph_spa_500_0_idp" "graph_spa_500_10_idp")
methodsArray=("sRR" "tRR" "myopic")
lRRArray=("lRR")
superArray=("supers" "supert")


# for str in ${xpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done


# for str in ${tpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done


# for str in ${thpArray[@]}; do
#   echo $str
# #   ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
# #   ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${hpArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sumf
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${idpArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${npArray[@]}; do
#   echo $str
#   # ./run sRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run tRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run myopic 261 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run lRR 251 10000 0.02 $str 10000 0.1 10 ic sum
#   # ./run supers 261 10000 0.02 $str 10000 0.1 10 ic sum
#   ./run supert 261 10000 0.02 $str 10000 0.1 10 ic sum
# done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 201 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 201 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     # ./run $str 101 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${methodsArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_thp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_thp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_thp 4000 0.1 10 ic sum
#     # ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# done


# for str in ${lRRArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     # ./run $str 91 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

# for str in ${lRRArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_thp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_thp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_thp 4000 0.1 10 ic sum
#     # ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
# done

# for str in ${superArray[@]}; do
#     echo $str
#     ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_tp 4000 0.1 10 ic sum
#     ./run $str 101 4000 0.01 soc-sign-bitcoinotc_tp 4000 0.1 10 ic sum
#     ./run $str 91 4000 0.01 facebook_combined_tp 4000 0.1 10 ic sum
#     # ./run $str 91 4000 0.01 twitter_combined_tp 4000 0.1 10 ic sum
# done

for str in ${superArray[@]}; do
    echo $str
    ./run $str 101 4000 0.01 soc-sign-bitcoinalpha_thp 4000 0.1 10 ic sum
    ./run $str 101 4000 0.01 soc-sign-bitcoinotc_thp 4000 0.1 10 ic sum
    ./run $str 91 4000 0.01 facebook_combined_thp 4000 0.1 10 ic sum
    # ./run $str 91 4000 0.01 twitter_combined_thp 4000 0.1 10 ic sum
done