# If not running interactively, don't do anything
[ -z "$PS1" ] && return
#if [ "${BASH}" -a "${-}" -o "$-" != "${-#i}" ] && tty -s; then # le shell est interactif

# oterm nous demande de faire un cd ?
[ "${OTERMPWD}" ] && cd "${OTERMPWD}"

if [ "`domainname`" = "cave.etoile.polymtl.ca" ]; then
  . /net/stk_bonne_fedora/sbin/site_init_vj2.2.0_osg1.6.sh
  export MALLOC_CHECK_=1 # free() error message is printed on stderr, but the program is not aborted
elif [ "`domainname`" = "info.polymtl.ca" ]; then
  : #
elif [ -d "/data/536" ]; then
  . /data/536/stk_bonne_fedora/sbin/site_init_vj2.2.0_osg1.6.sh
fi
alias vrjconfigBO='( . site_init_vj2.0.1_osg1.6.sh; JDK_HOME=/usr vrjconfig )'
CDPATH="$CDPATH:${JUGGLER_DIR}/.."

export U3D_SOURCE=/data/stk/pdf3d/U3D/U3D_A_061228_5/Source/

if [ ! "${BASH}" ]; then set -o nolog; set -o gmacs; fi

#    Find                 Esc[1~
#    Insert               Esc[2~
#    Remove               Esc[3~
#    Select               Esc[4~
#    Prior                Esc[5~
#    Next                 Esc[6~
if [ ! "${BASH}" ]; then
  #alias __145q=$(print "\020")  # fleche ^ = Ctrl-P
  #alias __6~=$(print "\020")  # fleche ^ = Ctrl-P
  alias __A=$(print "\020")  # fleche ^ = Ctrl-P
  alias __B=$(print "\016")  # fleche v = Ctrl-N
  alias __C=$(print "\006")  # fleche > = Ctrl-F
  alias __D=$(print "\002")  # fleche < = Ctrl-B
  alias __Z=$(print "\017")  # fleche v = Ctrl-O (pour remettre le G0 dans le GL)
  #alias __O=$(print "key")
  #alias __11='key1'
  #alias __2='key2'
  #alias __3='echo key3'
  #alias __4=$(print "key\n")
  #alias __5=$(print "\012")
fi

alias !!='fc -s'
alias !='fc -e -'
alias -- -='cd -'
alias ..='cd ..'
alias ,='/bin/pwd'
alias ,,='cd "`/bin/pwd -P 2>/dev/null || /bin/pwd`"'  # -P n'est pas supporte sur suse
#alias ,,,='cd "`/bin/pwd -P 2>/dev/null`"'
alias 1='fg %1'
alias 2='fg %2'
alias 3='fg %3'
alias 4='fg %4'
alias 5='fg %5'
alias 6='fg %6'
alias 7='fg %7'
alias 8='fg %8'
alias 9='fg %9'

alias cp='cp'   # au cas où ça soit une fonction!
alias mv='mv'   # au cas où ça soit une fonction!
alias rm='rm'   # au cas où ça soit une fonction!
alias man='man' # au cas où ça soit une fonction!

alias agi='sudo apt-get install'
alias agu='sudo apt-get update'
alias agg='sudo apt-get upgrade'
alias ags='sudo apt-cache search'
alias agsh='sudo apt-cache show'
alias agr='sudo apt-get remove'
#alias agd='sudo apt-get dist-upgrade'

#alias setlibpath='export LIBPATH=`(cd Vu)`; export LD_LIBRARY_PATH=`(cd Vu)`; export LD_LIBRARYN32_PATH=`(cd Vu)`; export SHLIB_PATH=`(cd Vu)`; export DYLD_LIBRARY_PATH=`(cd Vu)`'
#alias setlibmesa='export LIBPATH=${VUHOME}/lib/`${VUHOME}/bin/VuGetArch.sh`; export LD_LIBRARY_PATH=${VUHOME}/lib/`${VUHOME}/bin/VuGetArch.sh`; export LD_LIBRARYN32_PATH=${VUHOME}/lib/`${VUHOME}/bin/VuGetArch.sh`; export SHLIB_PATH=${VUHOME}/lib/`${VUHOME}/bin/VuGetArch.sh`'
alias cls='tput clear'
alias cta='cat'
alias d='date'
alias dc='cd'
alias disp='echo DISPLAY=${DISPLAY}'
alias disp0='DISPLAY=:0 export DISPLAY && disp'
alias disp1='DISPLAY=:1 export DISPLAY && disp'
alias dispv='DISPLAY=vis.dgi.polymtl.ca:0 export DISPLAY && disp'
alias disps='DISPLAY=`${HOME}/bin/setDISPLAY.sh` export DISPLAY && disp'
alias dispu='unset DISPLAY && disp'
alias e='${EDITOR}'
alias gh='ghostview'
alias h='history'
#alias httpgo='/etc/rc.httpd'
#alias httpstop='stopsrc -s httpd'
alias impman="a2ps -m -1 -p -ns -nH"
impraw() { if [ "$@" ]; then gs -q -dNOPAUSE -r600 -dBATCH -sDEVICE=ljet4 -sOutputFile=- ${1+"$@"} | lpr -PhpRAW; fi; }
convraw() { if [ "$@" ]; then gs -q -dNOPAUSE -r600 -dBATCH -sDEVICE=ljet4 -sOutputFile=- ${1+"$@"}; fi; }
alias j='jobs -l'
#keymap() { if [ "$1" ]; then N="$1"; else N=${LANG}; fi; xmodmap /usr/lpp/X11/defaults/xmodmap/${N}/keyboard; }
[ `uname` != Darwin ] && LSOPT="b" || LSOPT=""
alias kv='vu -kill || Vu -kill'
#alias kr='ps -fC sshd | awk "/@notty/ { print \"kill \"$2; }"'
alias ls='ls -F${LSOPT}'
alias LS=ls
alias l='ls -F${LSOPT}'
alias la='ls -F${LSOPT} -A'
alias ll='ls -F${LSOPT} -l'
alias LL=ll
alias lla='ls -F${LSOPT} -lA'
alias lal=lla
alias lld='ls -F${LSOPT} -ld'
if [ `uname` = 'AIX' ]; then alias ll='ls -F${LSOPT} -le'; fi
alias l.='ls -F${LSOPT} -d .*'
alias lh='ls -F${LSOPT} -l -t | head'
alias lt='ls -F${LSOPT} -l -rt | tail'
alias lat='ls -F${LSOPT} -l -Art | tail'
alias laty=lat
[ `uname` == Darwin ] && alias ldd="Otool -L"
alias loca="env | egrep '^LANG|^LC_[A-Z]'"
#alias unsetloca='unset LANG LC_COLLATE LC_CTYPE LC_MONETARY LC_NUMERIC LC_TIME LC_MESSAGES LC_ALL'
#alias unsetenvloca='unsetenv LANG LC_COLLATE LC_CTYPE LC_MONETARY LC_NUMERIC LC_TIME LC_MESSAGES LC_ALL'
alias mc='mv'
alias m='make'
alias M='make'
alias MAKE='make'
alias mail='Mail'
[ "`uname`" = "Linux" ] && alias mo='more' || alias mo='more -e'
alias MO='mo'
alias om='mo'
[ `uname` != Darwin ] && alias open="open.sh"
alias path='set | grep -i PATH'
alias pa='ps auxf | grep -v "^[ ]*root"'
alias pp='ps -ef | grep -v "^[ ]*root"'
rs() { eval `resize` || eval `echo LINES=\`termdef -l\`';' COLUMNS=\`termdef -c\`';' export COLUMNS LINES`; }
#alias s132="echo '\033[?3h' && rs"
#alias s80="echo '\033[?3l' && rs"
#alias sad='ssh-add'
alias vus='vu -Serv -noClient'
alias vum='vu -noServ -Client Motif'
alias vuc='vu -noServ -Client Cmd'
alias vux='vu -noServ -Client Wx'
#alias vuz='vu -noServ -Client Wz'
alias vui='vu -noServ -Client Input'
alias vul='Vu -ls -o /tmp/Vuls.log'
#alias vuj='vu -noServ -Client Java'
alias you='if test "$EUID" = 0 ; then /sbin/yast2 online_update ; else su - -c "/sbin/yast2 online_update" ; fi'
alias t='type'
whc() { cat `whence $1`; }
wh()
{
  export LC_MESSAGES=POSIX
  C=`( type $1 || echo $1 IS NOT FOUND ) | head -1 | cut -d' ' -f3`
  case "$C" in
    NOT)
      ;;
    hashed|brouill*) # fig2dev is hashed (/usr/X11R6/bin/fig2dev) | fig2dev est brouillé (/usr/X11R6/bin/fig2dev)
      type $1 | head -1
      N=`type $1 | cut -d' ' -f4 | cut -d'(' -f2 | cut -d')' -f1`
      ls -l $N
      file $N
      ( rpm -qf $N || dpkg -S $N || dpkg -S $M || true ) 2>/dev/null
      ;;
    a|une) # wh is a function | wh est une fonction
      type $1
      ;;
    aliased|l\'alias) # ls is aliased to `ls -F${LSOPT}' | ls possède l'alias `ls -F${LSOPT}'
      type $1 | head -1
      #C=`type $1 | cut -d' ' -f5 | head -1 | cut -c2- | cut -d"'" -f1`
      C=`type $1 | cut -d'\`' -f2 | sed "s/'//"`
      ( unalias $1; wh $C )
      ;;
    *) # Vu is /home/benoit/bin/Vu
      type $1 | head -1
      N=`type $1 | cut -d' ' -f3`; M=$N
      while [ ! -d $N ]; do
        ls -l $N; L=`/bin/ls -l $N`;
        P=`echo $L | awk -F'>' '/>/ {print substr($2,2)}'`; [ "${P}" ] || break
        if [ "`echo $P | cut -c1`" != "/" ]; then N=`dirname $N`/$P; else N=$P; fi
      done
      file $N
      ( rpm -qf $N || dpkg -S $N || dpkg -S $M || true ) 2>/dev/null
      ;;
  esac
}

aliasmaybe() { if type $2 >/dev/null 2>&1; then type $1 >/dev/null 2>&1 || alias $1=$2; fi; }
aliasmaybe f finger
aliasmaybe tn telnet
#aliasmaybe Info insight
#aliasmaybe Info helpview
#aliasmaybe pv xpsview
#aliasmaybe pv showps
aliasmaybe dbx adb
aliasmaybe dbx gdb
aliasmaybe whence which

if [ "${BASH}" ]; then
  ignoreeof=0
  IGNOREEOF=0
  alias print=echo
  notify=1
  command_oriented_history=1
# don't put duplicate lines in the history. See bash(1) for more options
# export HISTCONTROL=ignoredups
  cdable_vars=1
# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
  shopt -s checkwinsize
# make less more friendly for non-text input files, see lesspipe(1)
  [ -x /usr/bin/lesspipe ] && eval "$(lesspipe)"
# set variable identifying the chroot you work in (used in the prompt below)
  #if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
  #    debian_chroot=$(cat /etc/debian_chroot)
  #fi
  #PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
fi

#ulimit -t unlimited 2>/dev/null
#ulimit -d unlimited 2>/dev/null
#ulimit -s unlimited 2>/dev/null
ulimit -m `unset LC_MESSAGES; ulimit -H -m | xargs -n1 | tail -1`
ulimit -c `unset LC_MESSAGES; ulimit -H -c | xargs -n1 | tail -1`
case `domainname` in
    cave.etoile.polymtl.ca) ulimit -c 0; ;;
esac

for VULICFILE in \
 ${HOME}/lic/lic*.dat \
 ${TMPDIR}/lic*.dat \
 ${HOME}/lic*.dat \
 ${HOME}/*/Vu/license.dat \
 /apps/vu/Vu*/licenses/license.dat \
 "" ; do
  test -f "${VULICFILE}" && break
done
[ -z "${VULICFILE}" ] && unset VULICFILE || export VULICFILE

# CD
cdFunc()
{
  : ${cd_stack[0]=0}
  case "$*" in
    [0-9]*)
      cd ${cd_stack[$1]}
      ;;
    *)
      cd $*
      if [ ${cd_stack[${cd_stack[0]}]} != ${PWD} ]; then
        let cd_stack[0]=cd_stack[0]+1; cd_stack[${cd_stack[0]}]=${PWD}
      fi
      set | grep cd_stack | sed 's/cd_stack//'
      ;;
  esac
}

### get set and ... go !

if [ "${TERM}" -a ! "${EMACS}" ]; then
  if [ "`uname`" = "Linux" -a "${TERM}" = "dtterm" ]; then TERM="xterm"; fi
  _HOSTNAME="`hostname | cut -d. -f1`"
  # title and icon
  if [ "${TERM}" != "unknown" -a \
       "${TERM}" != "emacs" -a \
       "${TERM}" != "linux" -a \
       "${TERM}" != "vt100" -a \
       "${TERM}" != "vt220" -a \
       "${TERM}" != "eterm" ]; then
    if tty -s; then
      # Si PS2 n'est pas initialisé, c'est probablement parce
      # que c'est un nouveau shell qui débute. Alors on y va!
      # Si PS2 est initialisé, on dot être en train de faire quelque chose
      # dans le shell courant (envoyer un mail!). Ne rien faire afin de ne
      # rien perturber.
      if [ "${BASH}" -a "${PS2}" ]; then
        case `uname` in
          Linux*)  _UNAME=`uname -a | cut -d\  -f1,3`; ;;
          Darwin*) _UNAME=`uname -a | cut -d\  -f1,3`; ;;
          AIX)     _UNAME=`uname -a | cut -d\  -f1-2`" "`oslevel`; ;;
          HP-UX)   _UNAME=`uname -a | cut -d\  -f1-5`; ;;
          IRIX*)   _UNAME=`uname -a | cut -d\  -f1-3,5`'('`uname -R`')'; ;;
          *)       _UNAME=`uname -a`; ;;
        esac
        : ${LOGNAME:=`logname`}
        ${HOME}/bin/setTITLE.sh -1 "`echo ${LOGNAME} | cut -c1`@${_HOSTNAME}" 2>/dev/null
        ${HOME}/bin/setTITLE.sh -2 "${LOGNAME}@${_HOSTNAME} [${_UNAME}]" 2>/dev/null
        #PROMPT_COMMAND='echo -ne "\033]0;${USER}@${HOSTNAME} : ${PWD/$HOME/~}  ["'${_UNAME}'"] \007"'
        unset _UNAME
      fi
    fi
  fi


  # PS1
  # setaf (set ANSI foreground)
  # setab (set ANSI background)
  _HI=; _LO=;
  case ${TERM} in
    unknown)  ;;
    emacs)    ;;
    eterm)    _HI=`tput -Tdtterm setaf 5`; _LO=`tput -Tdtterm sgr0`; ;;
    xterm*)   _HI=`tput setaf 6`;          _LO=`tput sgr0`; ;;
    dtterm)   _HI=`tput setaf 6`;          _LO=`tput sgr0`; ;;
    linux)    _HI=`tput setaf 6`;          _LO=`tput sgr0`; ;;
    *rxvt*)   _HI=`tput setaf 6`;          _LO=`tput sgr0`; ;;
    vt100)    _HI=`tput smso`;             _LO=`tput rmso`; ;;
    vt220)    _HI=`tput smso`;             _LO=`tput rmso`; ;;
    *)        _HI=`tput smso`;             _LO=`tput sgr0`; ;;
    #*)       _HI=`tput sgr 1 0`;          _LO=`tput sgr0`; ;;
  esac
  if [ "${BASH}" ]; then
    _H2=${_LO}
    _H3=`tput setaf 3`;
    _H6=`tput setaf 6`;
    #PS1="\\[${_HI}\\]## \d \A \\[${_H3}\\]\u@\h\n\\[${_H3}\\]\w \\[${_LO}\\]\! \$ "
    PS1="\\[${_HI}\\]## \d \A \\[${_H3}\\]\u@\h\\[${_LO}\\]\n\w \! \$ "
  else
    #PS1="${_HOSTNAME} ${_HI}"'\w'"${_LO} $ "
    PS1="${_HOSTNAME} ${_HI}"'${PWD#${PWD%*/*/*/*/*/*}/}'"${_LO} $ "
  fi
  # pour Darwin/zsh
  #PROMPT="%m ${_HI}%d${_LO} $ "
  unset _HOSTNAME _HI _LO

fi
