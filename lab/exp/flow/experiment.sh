#!/usr/bin/env bash

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
ROOT_FOLDER=$(cd $SCRIPT_PATH && cd ../../../ && pwd)

SUMMARY_APP=$1

DATA_OUTPUT_FOLDER=${SCRIPT_PATH}/output
PLOT_OUTPUT_FOLDER=${SCRIPT_PATH}/output/plot

python3 ${SCRIPT_PATH}/experiment.py $ROOT_FOLDER cmake-build-release
${SCRIPT_PATH}/summary-flow.sh $SUMMARY_APP $DATA_OUTPUT_FOLDER


${SCRIPT_PATH}/plot-scripts/shape-grid.sh $DATA_OUTPUT_FOLDER $PLOT_OUTPUT_FOLDER ii 5 0.01000
${SCRIPT_PATH}/plot-scripts/shape-estimator.sh $DATA_OUTPUT_FOLDER $PLOT_OUTPUT_FOLDER 0.25 0.01000