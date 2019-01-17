INSTALL_PATH=/home-local/dantu1/GIT/PhD/exhaustive-gc/ext
BUILD_PATH=/home-local/dantu1/GIT/PhD/exhaustive-gc/ext-build

CMAKE_PREFIX_PATH=/home-local/dantu1/Documents/local_libs/lib

mkdir $BUILD_PATH
mkdir $INSTALL_PATH

cd $BUILD_PATH

DIPACUS_SOURCE_DIR=/home-local/dantu1/GIT/PhD/DIPaCUS
mkdir DIPaCUS
cd DIPaCUS

cmake $DIPACUS_SOURCE_DIR -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH
make
make install

cd ..


GEOC_SOURCE_DIR=/home-local/dantu1/GIT/PhD/GEOC
mkdir geoc
cd geoc

cmake $GEOC_SOURCE_DIR -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH
make
make install

cd ..


GCURVE_SOURCE_DIR=/home-local/dantu1/GIT/PhD/GCurve
mkdir gcurve
cd gcurve

cmake $GCURVE_SOURCE_DIR -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH \
-DDIPACUS_INCLUDE_DIRS=$INSTALL_PATH/include -DDIPACUS_LIBS_DIR=$INSTALL_PATH/lib
make
make install

cd ..


BOOST_INCLUDE_DIRS=/home-local/dantu1/Documents/local_libs/boost_1_66_0
LAZYC_SOURCE_DIR=/home-local/dantu1/GIT/PhD/lazy-combinator
mkdir lazy-comb
cd lazy-comb

cmake $LAZYC_SOURCE_DIR -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH \
-DBOOST_INCLUDE_DIRS=$BOOST_INCLUDE_DIRS
make
make install



