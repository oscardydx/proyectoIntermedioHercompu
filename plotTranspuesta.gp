set terminal pdf
set out 'report/transpuestaSinOptimizar.pdf'
set xlabel 'Dimension Matriz'
set ylabel 'MFLOPS'
set title  'Comparación de Operación Transpuesta Sin Optimizar'
plot 'datosTranspuesta.txt' using 2:11 w lp, 'datosTransArmadillo.txt' using 2:11 w lp,'datosEigentranspuesta.txt' using 2:11 w lp
