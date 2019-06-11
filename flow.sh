#!/usr/bin/env bash

PROJECT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
FLOW_APP=${PROJECT_FOLDER}/cmake-build-release/app/flow/exhaustive-gc-app-flow
OUTPUT_FOLDER=${PROJECT_FOLDER}/app/flow/output

${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e isqc -a 0 -S square -s best ${OUTPUT_FOLDER}/square/m2M30/J1/isqc-0/best&
${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e elastica -a 0.01 -S square -s best ${OUTPUT_FOLDER}/square/m2M30/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e elastica -a 0.001 -S square -s best ${OUTPUT_FOLDER}/square/m2M30/J1/elastica-0.001/best&

${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e isqc -a 0 -S flower -s best ${OUTPUT_FOLDER}/flower/m2M30/J1/isqc-0/best&
${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e elastica -a 0.01 -S flower -s best ${OUTPUT_FOLDER}/flower/m2M30/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 30 -j 1 -i 100 -e elastica -a 0.001 -S flower -s best ${OUTPUT_FOLDER}/flower/m2M30/J1/elastica-0.001/best

