cmd_/home/tuan/work/kenel/modules.order := {   echo /home/tuan/work/kenel/hello.ko; :; } | awk '!x[$$0]++' - > /home/tuan/work/kenel/modules.order
