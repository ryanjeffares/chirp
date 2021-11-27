<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
<CsInstruments>

nchnls = 2
0dbfs = 1

instr 1
iAmp = p4
iFreq = p5 
aSig oscil iAmp, iFreq
outs aSig, aSig 
endin 

</CsInstruments>
<CsScore>
i1 0 1 0.5 220
i1 1 1 0.5 440
i1 2 1 0.5 880
</CsScore>
</CsoundSynthesizer>
