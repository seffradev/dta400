simple Txc1
{
    gates:
        input in;
        output out;
}

network Tiktok1
{
    @display("bgb=397,146");
    submodules:
        tik: Txc1 {
            @display("p=45,90");
        }
        tok: Txc1 {
            @display("p=175,29");
        }
    connections:
        tik.out --> {  delay = 100ms; } --> tok.in;
        tik.in <-- {  delay = 100ms; } <-- tok.out;
}
