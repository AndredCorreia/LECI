transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {/home/andre/Desktop/Universidade/1ano2semestre/LSD/aula07/Dec2_4En.vhd}

