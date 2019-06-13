import subprocess,sys,os

PROJECT_FOLDER="set-via-parameter"
BIN_FOLDER="set-in-read-input"
SCRIPT_FOLDER="set-in-read-input"
BASE_OUTPUT_FOLDER="set-in-read-input"

def recCombinations(maxList,curr,combList):

    if len(maxList)==0:
        combList.append(curr)
        return

    for el in range(0,maxList[0]):
        recCombinations(maxList[1:],curr+[el],combList)

def combinations(configList):
    numParams = len(configList)
    maxList = [ len(el) for el,_ in configList ]

    combList=[]
    recCombinations(maxList,[],combList)

    for c in combList:
        yield tuple( configList[i][0][c[i]] for i in range(numParams) )


GRID_STEP=[1.0,0.5,0.25]
SHAPES=["wave","square","flower","ball","triangle","pentagon","ellipse"]#"heptagon"]
RADIUS=[1,2,3,5]
ESTIMATOR=["mdca","ii"]
ENERGY=["sqc","isqc","elastica"]
LENGTH_PENALIZATION=[0,0.1,0.01,0.005]
ITERATIONS=[100]
MIN_CURVE_LENGTH=[2]
MAX_CURVE_LENGTH=[5,10,20,30]
NUM_JONCTIONS=[1]
STRATEGY=["best"]


CONFIG_LIST=[ (GRID_STEP,"grid_step"),
              (SHAPES,"shape"), (RADIUS,"radius"), (ITERATIONS,"iterations"),
              (ESTIMATOR,"estimator"),(ENERGY,"energy"),(LENGTH_PENALIZATION,"length_pen"),
              (MIN_CURVE_LENGTH,"mLength"),(MAX_CURVE_LENGTH,"MLength"),(NUM_JONCTIONS,"jonctions"),
              (STRATEGY,"strategy")]


def valid_combination(c):
    gs,shape,radius,iterations,estimator,energy,length_pen,mLength,MLength,jonctions,strategy = c

    flag=True
    if energy!="elastica":
        flag=flag and length_pen==0

    if estimator=="mdca":
        flag= flag and radius==1

    if estimator=="ii":
        flag=flag and length_pen==0 and mLength==2 and MLength==5 and jonctions==1 and strategy=="best"

    return flag

def resolve_output_folder(gs,shape,radius,iterations,estimator,energy,length_pen,mLength,MLength,jonctions,strategy):
    outputFolder = "%s/%s/radius_%d/%s/%s/len_pen_%.2f/m%dM%d/jonctions_%d/%s/gs_%.2f" % (BASE_OUTPUT_FOLDER,shape,radius,
                                                                                          estimator,energy,length_pen,
                                                                                          mLength,MLength,jonctions,strategy,
                                                                                          gs)

    return outputFolder

def flow(c):

    outputFolder = resolve_output_folder(*c)
    gs,shape,radius,iterations,estimator,energy,length_pen,mLength,MLength,jonctions,strategy = c

    binary = "%s/%s" % (BIN_FOLDER,"flow/exhaustive-gc-app-flow")
    subprocess.call( [binary,
                      "%s%s" % ("-S",shape),
                      "%s%d" % ("-r",radius),
                      "%s%d" % ("-i",iterations),
                      "%s%s" % ("-e",energy),
                      "%s%f" % ("-a",length_pen),
                      "%s%f" % ("-m",mLength),
                      "%s%f" % ("-M",MLength),
                      "%s%f" % ("-j",jonctions),
                      "%s%s" % ("-s",strategy),
                      "%s%f" % ("-h", gs),
                      outputFolder
                      ] )

    s=" ".join([binary,
                "%s%s" % ("-S",shape),
                "%s%d" % ("-r",radius),
                "%s%d" % ("-i",iterations),
                "%s%s" % ("-e",energy),
                "%s%f" % ("-a",length_pen),
                "%s%f" % ("-m",mLength),
                "%s%f" % ("-M",MLength),
                "%s%f" % ("-j",jonctions),
                "%s%s" % ("-s",strategy),
                "%s%f" % ("-h", gs),
                outputFolder
                ])


def total_combinations():
    total=0
    combs = combinations(CONFIG_LIST)
    for c in combs:
        if valid_combination(c):
            total+=1
    return total

def read_input():
    if len(sys.argv)<3:
        print("Parameters missing! PROJECT_FOLDER RELATIVE_BUILD_FOLDER")
        exit(1)

    global PROJECT_FOLDER,BIN_FOLDER, BASE_OUTPUT_FOLDER, SCRIPT_FOLDER
    PROJECT_FOLDER=sys.argv[1]
    BIN_FOLDER="%s/%s/%s" % (PROJECT_FOLDER,sys.argv[2],"app")
    BASE_OUTPUT_FOLDER="%s/%s" % (PROJECT_FOLDER,"lab/exp/flow/output")

def main():
    read_input()
    print("Total combinations: ",total_combinations())
    for c in combinations(CONFIG_LIST):
        if valid_combination(c):
            flow(c)



if __name__=='__main__':
    main()
