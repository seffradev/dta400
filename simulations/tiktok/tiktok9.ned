simple Tik9
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Tok9
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
        output out;
}

network Tiktok9
{
    @display("bgb=399,149");
    submodules:
        tik: Tik9 {
            parameters:
                @display("i=,cyan");
        }
        tok: Tok9 {
            parameters:
                @display("i=,gold");
        }
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
