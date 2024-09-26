simple Tik8
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Tok8
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
        output out;
}

network Tiktok8
{
    @display("bgb=388,148");
    submodules:
        tik: Tik8 {
            parameters:
                @display("i=,cyan");
        }
        tok: Tok8 {
            parameters:
                @display("i=,gold");
        }
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
