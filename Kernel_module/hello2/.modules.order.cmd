cmd_/home/tuan/work/kenel/hello2/modules.order := {   echo /home/tuan/work/kenel/hello2/hello2.ko; :; } | awk '!x[$$0]++' - > /home/tuan/work/kenel/hello2/modules.order
