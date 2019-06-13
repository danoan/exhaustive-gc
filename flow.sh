#!/usr/bin/env bash

PROJECT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
FLOW_APP=${PROJECT_FOLDER}/build-release/app/flow/exhaustive-gc-app-flow
OUTPUT_FOLDER=${PROJECT_FOLDER}/app/flow/output

${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h1.0 -e isqc -a 0 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h1.0/m2M20/J1/isqc-0/best&
${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h1.0 -e elastica -a 0.01 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h1.0/m2M20/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h1.0 -e elastica -a 0.001 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h1.0/m2M20/J1/elastica-0.001/best

${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h0.5 -e elastica -a 0.01 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h0.5/m2M20/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h0.5 -e elastica -a 0.001 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h0.5/m2M20/J1/elastica-0.001/best

${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h0.25 -e elastica -a 0.01 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h0.25/m2M20/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 20 -j 1 -i 100 -r3 -h0.25 -e elastica -a 0.001 -S square -s best ${OUTPUT_FOLDER}/square/radius3/h0.25/m21M20/J1/elastica-0.001/best




${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h1.0 -e isqc -a 0 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h1.0/m1M5/J1/isqc-0/best&
${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h1.0 -e elastica -a 0.01 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h1.0/m1M5/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h1.0 -e elastica -a 0.001 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h1.0/m1M5/J1/elastica-0.001/best

${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h0.5 -e elastica -a 0.01 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h0.5/m1M5/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h0.5 -e elastica -a 0.001 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h0.5/m1M5/J1/elastica-0.001/best

${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h0.25 -e elastica -a 0.01 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h0.25/m1M5/J1/elastica-0.01/best&
${FLOW_APP} -m 2 -M 5 -j 1 -i 100 -r3 -h0.25 -e elastica -a 0.001 -S flower -s best ${OUTPUT_FOLDER}/flower/radius3/h0.25/m1M5/J1/elastica-0.001/best
