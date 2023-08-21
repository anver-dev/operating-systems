#!/usr/bin/bash

for maquina in $(cat maquinas);
do
 online=$(nc -z $maquina 22 > /dev/null)
   if [ $? == 0 ]; then
      l1=$(ssh $maquina "lscpu | grep 'L1' | awk '{print \$3}'")
      l2=$(ssh $maquina "lscpu | grep 'L2' | awk '{print \$3}'")
      l3=$(ssh $maquina "lscpu | grep 'L3' | awk '{print \$3}'")
      echo "Maquina: "$maquina" L1:"$l1" L2:"$l2" L3:"$l3
   else

      echo "Maquina offline: "$maquina   
   fi
done
