cmd_/home/tuan/work/kenel/Module.symvers := sed 's/\.ko$$/\.o/' /home/tuan/work/kenel/modules.order | scripts/mod/modpost -m -a  -o /home/tuan/work/kenel/Module.symvers -e -i Module.symvers   -T -
