#!/bin/bash
#
# install.sh
#
# Runs through the basic steps to install.  We do make certain assumptions
# in order to facilitate the setup.  In particular, we assume we are running
# from the install wwivbase location.

WWIVBASE=`pwd`
LOGFILE=install_`date "+%Y-%m-%d_%H-%M-%S"`.log

echo
echo "Starting the install process"
echo "Starting the install process" > ${WWIVBASE}/$LOGFILE 2>&1
echo

#
# Make sure we have the necessary tools
#
# checking for unzip shouldn't be necessary (since we needed unzip 
# to get this file in the first place)
#
which unzip >> ${WWIVBASE}/$LOGFILE 2>&1
STATUS=$?

if [ "$STATUS" -ne "0" ]
then 
    echo "unzip utility is missing.  Please install it and run install again" 
    echo "unzip utility is missing.  Please install it and run install again" >> ${WWIVBASE}/$LOGFILE 2>&1
    exit 1
fi

# Make sure init exists
if [ ! -f ${WWIVBASE}/init ]
then
    echo "init is missing.  Please compile your BBS files and copy them"
    echo "init is missing.  Please compile your BBS files and copy them" >> ${WWIVBASE}/$LOGFILE 2>&1
    echo "to ${WWIVBASE} and run sh install.sh again."
    echo "to ${WWIVBASE} and run sh install.sh again." >> ${WWIVBASE}/$LOGFILE 2>&1
    exit 1
fi

#
# backup Windows binaries since we don't use them and they cause conflicts
#
echo 
echo "Moving Windows binaries"
echo "Moving Windows binaries" >> ${WWIVBASE}/$LOGFILE 2>&1
mkdir win-bins
mv *.exe win-bins


#
# Unzip the data files
#
echo
echo "Configuring data directories"
echo "Configuring data directories" >> ${WWIVBASE}/$LOGFILE 2>&1

# make directories
if [ ! -d gfiles ]
then 
    mkdir gfiles >> ${WWIVBASE}/$LOGFILE 2>&1
fi

if [ ! -d data ]
then 
    mkdir data >> ${WWIVBASE}/$LOGFILE 2>&1
fi

# unzip menus
cd gfiles
unzip -u ../en-menus.zip >> ${WWIVBASE}/$LOGFILE 2>&1
cd ${WWIVBASE}

# unzip regions
cd data
unzip -u ../regions.zip >> ${WWIVBASE}/$LOGFILE 2>&1
cd ${WWIVBASE}

# unzip zip-city
cd data
unzip -u ../zip-city.zip >> ${WWIVBASE}/$LOGFILE 2>&1
cd ${WWIVBASE}


# configure scripts and helper binaries.
echo "Configuring system scripts"
echo "Configuring system scripts" >> ${WWIVBASE}/$LOGFILE 2>&1

tar zxvf unix-scripts.tgz >> ${WWIVBASE}/$LOGFILE 2>&1

echo
echo "Setting file permissions"
echo "Setting file permissions" >> ${WWIVBASE}/$LOGFILE 2>&1
chmod 600 .fetchmailrc .procmailrc >> ${WWIVBASE}/$LOGFILE 2>&1

echo
echo "Setting scripts to use your install location ${WWIVBASE}"
echo "Setting scripts to use your install location ${WWIVBASE}" >> ${WWIVBASE}/$LOGFILE 2>&1
for i in bin/callout.py in.nodemgr wwiv-service .procmailrc .wwivrc
do
    sed -i "s@REPLACE-WWIVBASE@${WWIVBASE}@" $i
done

echo
echo "Your BBS basic data setup is complete."
echo "running ./init now to finalize the BBS.  "
sleep 5

cd ${WWIVBASE}
./init

echo
echo "init complete.  Please run ./bbs to login "
echo "and set up a new user to be the sysop (#1) account"
echo
