# Initialisations pour la cave

# installation dir
if [ "`domainname`" = "info.polymtl.ca" ]; then
  INSTDIR="/usr/local/cours/inf6802/packages"
elif [ -d "/data/536" ]; then
  INSTDIR="/data/536/stk_bonne_fedora/packages"
  export PATH="$PATH:/data/536/stk_bonne_fedora/bin" # pour le script startCAVE
else # domainname = "cave.etoile.polymtl.ca"
  INSTDIR="/net/stk_bonne_fedora/packages"
  export PATH="$PATH:/net/stk_bonne_fedora/bin" # pour le script startCAVE
fi

# VR Juggler 2.2.0
export JUGGLER_DIR=${INSTDIR}
export VJ_BASE_DIR=${JUGGLER_DIR}/usr
export JCCL_BASE_DIR=${VJ_BASE_DIR}
export TWEEK_BASE_DIR=${VJ_BASE_DIR}
export LD_LIBRARY_PATH=${VJ_BASE_DIR}/lib:${VJ_BASE_DIR}/lib/gadgeteer/plugins:$LD_LIBRARY_PATH
export VJ_CONFIG_DIR=${VJ_BASE_DIR}/share/vrjuggler/data/configFiles
export VJ_CFG_PATH=${INSTDIR}/../jconf:${VJ_BASE_DIR}/share/vrjuggler/data/configFiles:
export PATH=${VJ_BASE_DIR}/bin:$PATH
#export VPR_DEBUG_NFY_LEVEL=5

# OpenSceneGraph 2.6
export OSGHOME=${INSTDIR}/usr
export LD_LIBRARY_PATH=${OSGHOME}/lib:$LD_LIBRARY_PATH
export PATH=${OSGHOME}/bin:$PATH

# OpenSG 1.6.0
export OSGROOT=${INSTDIR}/usr
export LD_LIBRARY_PATH=${OSGROOT}/lib:$LD_LIBRARY_PATH

export PATH=${OSGROOT}/bin:$PATH

# fmodapi-4.02.00
export FMODROOT=${INSTDIR}/fmodapi-4.02.00/api
export LD_LIBRARY_PATH=${FMODROOT}/lib:$LD_LIBRARY_PATH

# OpenAL-1.1
export OPENALROOT=${INSTDIR}/OpenAL-1.1
export LD_LIBRARY_PATH=${OPENALROOT}/lib:$LD_LIBRARY_PATH

# QT 3.3.2
export QTDIR=/net/stk_bonne/packages/qt
export PATH=$QTDIR/bin:$PATH
export MANPATH=$QTDIR/doc/man:$MANPATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

# omniORB
export PYTHONPATH=${INSTDIR}/usr/lib/python2.3/site-packages:${PYTHONPATH}

# flagpoll (Path pour trouver doozer)
export FLAGPOLL_PATH=${JUGGLER_DIR}/usr/share/flagpoll

# ménage
unset INSTDIR
