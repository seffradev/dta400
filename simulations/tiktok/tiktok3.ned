simple Txc3
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

network Tiktok3
{
    @display("bgb=397,146");
    submodules:
        tik: Txc3 {
            parameters:
                @display("i=,cyan");
        }
        tok: Txc3 {
            parameters:
                @display("i=,gold");
        }
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
