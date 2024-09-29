simple Txc17
{
    parameters:
        @signal[arrival](type="long");
        @statistic[hopCount](title="hop count"; source="arrival"; record=vector,stats; interpolationmode=none);
        @display("i=block/routing");
    gates:
        inout gate[];
}

network Tiktok17
{
    parameters:
        @figure[description](type=text; pos=5,20; font=,,bold;
                             text="Random routing example - displaying last hopCount");
        @figure[lasthopcount](type=text; pos=5,35; text="Last hopCount: N/A");
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tik[6]: Txc17;
    connections:
        tik[0].gate++ <--> Channel <--> tik[1].gate++;
        tik[1].gate++ <--> Channel <--> tik[2].gate++;
        tik[1].gate++ <--> Channel <--> tik[4].gate++;
        tik[3].gate++ <--> Channel <--> tik[4].gate++;
        tik[4].gate++ <--> Channel <--> tik[5].gate++;
}

