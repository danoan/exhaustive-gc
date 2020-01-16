#!/usr/bin/env bash


SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

SUMMARY_APP=$1
DATA_FOLDER=$( realpath $2 )

find $DATA_FOLDER -name "inputData.txt" | xargs -I{} realpath {} | xargs -I{} dirname {} | xargs -I{} $SUMMARY_APP {} {}/summary.eps -j 5
