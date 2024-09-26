simple Txc6
{
    parameters:
        bool sendMsgOnInit = default(false);
        int limit = default(2);
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Tik6 extends Txc6
{
    parameters:
        @display("i=,cyan");
        sendMsgOnInit = true;
}

simple Tok6 extends Txc6
{
    parameters:
        sendMsgOnInit = false;
        @display("i=,gold");
}

network Tiktok6
{
    @display("bgb=397,146");
    submodules:
        tik: Tik6;
        tok: Tok6;
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
