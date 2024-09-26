simple Txc7
{
    parameters:
        volatile double delayTime @unit(s);
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Tik7 extends Txc7
{
    parameters:
        @display("i=,cyan");
}

simple Tok7 extends Txc7
{
    parameters:
        @display("i=,gold");
}

network Tiktok7
{
    @display("bgb=397,147");
    submodules:
        tik: Tik7;
        tok: Tok7;
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
