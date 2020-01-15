#!/usr/bin/env bash

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
DATA_FOLDER=$( realpath $1 )
OUTPUT_FOLDER=$2
ESTIMATOR=$3
RADIUS=$4
LENGTH_PEN=$5

source "${SCRIPT_PATH}/graph-plot.sh"

gp_last_plot()
{
	printf "'$1' u 1:2 w lp ls $3 title '$2';"
	gp_optimal_line
}

mkdir -p $OUTPUT_FOLDER

shapes="bean square flower triangle ellipse"

for s in $shapes
do
    PREFIX_INPUT="$DATA_FOLDER/$s/radius_$RADIUS/$ESTIMATOR/elastica/len_pen_$LENGTH_PEN/jonctions_1/best/gs_"
    OUTPUT_FILEFOLDER="$OUTPUT_FOLDER/$ESTIMATOR/radius_$RADIUS/length_pen_$LENGTH_PEN"

    mkdir -p $OUTPUT_FILEFOLDER

    create_multiplot "$OUTPUT_FILEFOLDER/$s.eps" "$s" "${PREFIX_INPUT}1.00000/energy.txt" "gs=1.0" \
    "${PREFIX_INPUT}0.50000/energy.txt" "gs=0.5" "${PREFIX_INPUT}0.25000/energy.txt" "gs=0.25"
done