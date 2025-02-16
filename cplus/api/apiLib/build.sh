
#cd build && rm ./* -fr
# build

# 编译命令
# ./build.sh   run  | grep 'App start' | wc -l

if [ $1 == build ]; then
cd build
rm ./* -fr
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                       -DbuildLib=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                       -DbuildArg=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                     -DbuildExcel=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                    -DbuildString=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                       -DbuildXml=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                       -DbuildLog=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                      -DbuildTest=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                               -DbuildLocalServer=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                               -DbuildLocalClient=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                -DbuildDbusClient=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                -DbuildDbusServer=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                            -DbuildNetconf2Client=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                            -DbuildNetconf2Server=1; make
#ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;cmake ../                                      -DbuildIpcs=1; make
ls | grep -v  -E 'App|lib|ApBeforep|ApAfterp' | xargs rm -fr;

ls *App  | wc -l
ls *ApBeforep  | wc -l
ls *ApAfterp   | wc -l
ls lib*  | wc -l
fi

#run
if [ $1 == run ]; then
EXE_DIR=build
ls ${EXE_DIR}/*ApBeforep  | wc -l
for file in `ls ${EXE_DIR}/*ApBeforep`; do
   ./${file}&
done

EXE_DIR=build
ls ${EXE_DIR}/*ApAfterp  | wc -l
for file in `ls ${EXE_DIR}/*ApAfterp`; do
   ./${file}
done

EXE_DIR=build
ls ${EXE_DIR}/*App  | wc -l
for file in `ls ${EXE_DIR}/*App`; do
   ./${file}
done
fi

#doc
if [ $1 == doc ]; then
    cd doc/apiLibDoc
    rm ./* -fr
    cmake ../../   -DapiLibDoc=1
    make doc
fi