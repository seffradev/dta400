simple Txc12
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];
}

network Tiktok12
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tik[6]: Txc12;
    connections:
        tik[0].gate++ <--> Channel <--> tik[1].gate++;
        tik[1].gate++ <--> Channel <--> tik[2].gate++;
        tik[1].gate++ <--> Channel <--> tik[4].gate++;
        tik[3].gate++ <--> Channel <--> tik[4].gate++;
        tik[4].gate++ <--> Channel <--> tik[5].gate++;
}

