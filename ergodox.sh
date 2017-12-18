MASTER=right

processHalf()
{
    WHICH=$1
    if [ "$WHICH" = "$MASTER" ]; then
        ADD_OPT="MASTER=$WHICH"
    fi

    echo "Plug in ${WHICH} half"
    read s
    make ergodox_infinity:lyuts $ADD_OPT
    sudo make ergodox_infinity:lyuts:dfu-util DFU_ARGS="--device 1c11:b007" VISUALIZER_ENABLE=yes LCD_BACKLIGHT_ENABLE=yes LCD_ENABLE=yes $ADD_OPT
}

processHalf left
processHalf right
