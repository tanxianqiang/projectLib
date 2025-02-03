
#cd build && rm ./* -fr
# build

# 编译命令
# ./build.sh   run  | grep 'App start' | wc -l

if [ $1 == build ]; then
cd build
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                       -DbuildLib=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                               -DbuildLocalServer=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                       -DbuildArg=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                     -DbuildExcel=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                               -DbuildLocalClient=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                    -DbuildString=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                       -DbuildXml=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                       -DbuildLog=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                      -DbuildTest=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                -DbuildDbusClient=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                -DbuildDbusServer=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                            -DbuildNetconf2Client=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                            -DbuildNetconf2Server=1; make
ls | grep -v  -E 'App|lib' | xargs rm -fr;cmake ../                                      -DbuildIpcs=1; make
ls | grep -v  -E 'App|lib|ko' | xargs rm -fr;

ls *App  | wc -l
ls *ko  | wc -l
ls lib*  | wc -l
fi

#run
if [ $1 == run ]; then
EXE_DIR=build
cd ${EXE_DIR}
ls *App  | wc -l
for file in `ls *App`; do
   `./${file} &`
done
fi


