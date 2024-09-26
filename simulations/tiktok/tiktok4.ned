simple Txc4
{
    parameters:
        bool sendMsgOnInit = default(false);
        int limit = default(2);
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

network Tiktok4
{
    @display("bgb=397,146");
    submodules:
        tik: Txc4 {
            parameters:
                sendMsgOnInit = true;
                @display("i=,cyan");
        }
        tok: Txc4 {
            parameters:
                sendMsgOnInit = false;
                @display("i=,gold");
        }
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
