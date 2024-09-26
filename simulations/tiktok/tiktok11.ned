simple Txc11
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];
        output out[];
}

network Tiktok11
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tik[6]: Txc11;
    connections:
        tik[0].out++ --> Channel --> tik[1].in++;
        tik[0].in++ <-- Channel <-- tik[1].out++;

        tik[1].out++ --> Channel --> tik[2].in++;
        tik[1].in++ <-- Channel <-- tik[2].out++;

        tik[1].out++ --> Channel --> tik[4].in++;
        tik[1].in++ <-- Channel <-- tik[4].out++;

        tik[3].out++ --> Channel --> tik[4].in++;
        tik[3].in++ <-- Channel <-- tik[4].out++;

        tik[4].out++ --> Channel --> tik[5].in++;
        tik[4].in++ <-- Channel <-- tik[5].out++;
}

