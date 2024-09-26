simple Txc10
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];
        output out[];
}

network Tiktok10
{
    submodules:
        tik[6]: Txc10;
    connections:
        tik[0].out++ --> {  delay = 100ms; } --> tik[1].in++;
        tik[0].in++ <-- {  delay = 100ms; } <-- tik[1].out++;

        tik[1].out++ --> {  delay = 100ms; } --> tik[2].in++;
        tik[1].in++ <-- {  delay = 100ms; } <-- tik[2].out++;

        tik[1].out++ --> {  delay = 100ms; } --> tik[4].in++;
        tik[1].in++ <-- {  delay = 100ms; } <-- tik[4].out++;

        tik[3].out++ --> {  delay = 100ms; } --> tik[4].in++;
        tik[3].in++ <-- {  delay = 100ms; } <-- tik[4].out++;

        tik[4].out++ --> {  delay = 100ms; } --> tik[5].in++;
        tik[4].in++ <-- {  delay = 100ms; } <-- tik[5].out++;
}

