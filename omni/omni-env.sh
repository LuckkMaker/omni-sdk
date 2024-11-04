# Check if we are running on Windows
if uname | grep -q "MINGW"; then
    win_build=1
    pwd_opt="-W"
else
    win_build=0
    pwd_opt=""
fi

# Set the base directory
export OMNI_BASE=$( builtin cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd ${pwd_opt})
unset pwd_opt