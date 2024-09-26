simple Txc5
{
    parameters:
        bool sendMsgOnInit = default(false);
        int limit = default(2);
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Tik5 extends Txc5
{
    parameters:
        @display("i=,cyan");
        sendMsgOnInit = true;
}

simple Tok5 extends Txc5
{
    parameters:
        sendMsgOnInit = false;
        @display("i=,gold");
}

network Tiktok5
{
    @display("bgb=397,146");
    submodules:
        tik: Tik5;
        tok: Tok5;
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
