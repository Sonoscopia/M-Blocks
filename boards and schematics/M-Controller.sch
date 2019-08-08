<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A3L-LOC">
<wire x1="288.29" y1="3.81" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="3.81" x2="373.38" y2="3.81" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="383.54" y2="3.81" width="0.1016" layer="94"/>
<wire x1="383.54" y1="3.81" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="383.54" y1="8.89" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="383.54" y1="13.97" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="383.54" y1="19.05" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="3.81" x2="288.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="288.29" y1="24.13" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="342.265" y1="24.13" x2="383.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="373.38" y1="3.81" x2="373.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="383.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="373.38" y1="8.89" x2="342.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="342.265" y1="8.89" x2="342.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="383.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="342.265" y1="13.97" x2="342.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="383.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="342.265" y1="19.05" x2="342.265" y2="24.13" width="0.1016" layer="94"/>
<text x="344.17" y="15.24" size="2.54" layer="94">&gt;DRAWING_NAME</text>
<text x="344.17" y="10.16" size="2.286" layer="94">&gt;LAST_DATE_TIME</text>
<text x="357.505" y="5.08" size="2.54" layer="94">&gt;SHEET</text>
<text x="343.916" y="4.953" size="2.54" layer="94">Sheet:</text>
<frame x1="0" y1="0" x2="387.35" y2="260.35" columns="8" rows="5" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A3L-LOC" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A3, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A3L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Arduino-clone">
<description>Arduino Clone pinheaders
By cl@xganon.com
http://www.xganon.com</description>
<packages>
<package name="PRO-MINI-2">
<pad name="TX0" x="-8.89" y="12.7" drill="0.8" shape="long"/>
<pad name="RX1" x="-8.89" y="10.16" drill="0.8" shape="long"/>
<pad name="RST1" x="-8.89" y="7.62" drill="0.8" shape="long"/>
<pad name="GND1" x="-8.89" y="5.08" drill="0.8" shape="long"/>
<pad name="D2" x="-8.89" y="2.54" drill="0.8" shape="long"/>
<pad name="D3" x="-8.89" y="0" drill="0.8" shape="long"/>
<pad name="D4" x="-8.89" y="-2.54" drill="0.8" shape="long"/>
<pad name="D5" x="-8.89" y="-5.08" drill="0.8" shape="long"/>
<pad name="D6" x="-8.89" y="-7.62" drill="0.8" shape="long"/>
<pad name="D7" x="-8.89" y="-10.16" drill="0.8" shape="long"/>
<pad name="D8" x="-8.89" y="-12.7" drill="0.8" shape="long"/>
<pad name="D9" x="-8.89" y="-15.24" drill="0.8" shape="long"/>
<pad name="RAW" x="6.35" y="12.7" drill="0.8" shape="long"/>
<pad name="GND" x="6.35" y="10.16" drill="0.8" shape="long"/>
<pad name="RST" x="6.35" y="7.62" drill="0.8" shape="long"/>
<pad name="VCC" x="6.35" y="5.08" drill="0.8" shape="long"/>
<pad name="A0" x="6.35" y="2.54" drill="0.8" shape="long"/>
<pad name="A1" x="6.35" y="0" drill="0.8" shape="long"/>
<pad name="A2" x="6.35" y="-2.54" drill="0.8" shape="long"/>
<pad name="A3" x="6.35" y="-5.08" drill="0.8" shape="long"/>
<pad name="D13" x="6.35" y="-7.62" drill="0.8" shape="long"/>
<pad name="D12" x="6.35" y="-10.16" drill="0.8" shape="long"/>
<pad name="D11" x="6.35" y="-12.7" drill="0.8" shape="long"/>
<pad name="D10" x="6.35" y="-15.24" drill="0.8" shape="long"/>
<pad name="GND2" x="-7.62" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="GND3" x="-5.08" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="VCC1" x="-2.54" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="RX1-1" x="0" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="TX0-1" x="2.54" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="DTR" x="5.08" y="15.24" drill="0.8" shape="long" rot="R90"/>
<pad name="A6" x="2.54" y="-8.89" drill="0.8" shape="long" rot="R180"/>
<pad name="A7" x="2.54" y="-6.35" drill="0.8" shape="long" rot="R180"/>
<pad name="A4" x="2.54" y="1.27" drill="0.8" shape="long" rot="R180"/>
<pad name="A5" x="2.54" y="3.81" drill="0.8" shape="long" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="PRO-MINI-2">
<pin name="GND3" x="-7.62" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="GND4" x="-5.08" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="VCC1" x="-2.54" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="RX1-1" x="0" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="TX0-1" x="2.54" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="DTR" x="5.08" y="25.4" visible="pin" length="middle" rot="R270"/>
<pin name="TX0" x="-22.86" y="12.7" visible="pin" length="middle"/>
<pin name="RX1" x="-22.86" y="10.16" visible="pin" length="middle"/>
<pin name="RST1" x="-22.86" y="7.62" visible="pin" length="middle"/>
<pin name="GND2" x="-22.86" y="5.08" visible="pin" length="middle"/>
<pin name="D2" x="-22.86" y="2.54" visible="pin" length="middle"/>
<pin name="D3" x="-22.86" y="0" visible="pin" length="middle"/>
<pin name="D4" x="-22.86" y="-2.54" visible="pin" length="middle"/>
<pin name="D5" x="-22.86" y="-5.08" visible="pin" length="middle"/>
<pin name="D6" x="-22.86" y="-7.62" visible="pin" length="middle"/>
<pin name="D7" x="-22.86" y="-10.16" visible="pin" length="middle"/>
<pin name="D8" x="-22.86" y="-12.7" visible="pin" length="middle"/>
<pin name="D9" x="-22.86" y="-15.24" visible="pin" length="middle"/>
<pin name="RAW" x="20.32" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="GND" x="20.32" y="10.16" visible="pin" length="middle" rot="R180"/>
<pin name="RST" x="20.32" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="VCC" x="20.32" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="A3" x="20.32" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="A2" x="20.32" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="A1" x="20.32" y="-2.54" visible="pin" length="middle" rot="R180"/>
<pin name="A0" x="20.32" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="D13" x="20.32" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="D12" x="20.32" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="D11" x="20.32" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D10" x="20.32" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="A7" x="2.54" y="-2.54" visible="pin" length="point" rot="R180"/>
<pin name="A6" x="2.54" y="-5.08" visible="pin" length="point" rot="R180"/>
<pin name="A5" x="2.54" y="5.08" visible="pin" length="point" rot="R180"/>
<pin name="A4" x="2.54" y="2.54" visible="pin" length="point" rot="R180"/>
<wire x1="-17.78" y1="20.32" x2="15.24" y2="20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="20.32" x2="15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="-17.78" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-20.32" x2="-17.78" y2="20.32" width="0.254" layer="94"/>
<text x="-5.08" y="-12.7" size="1.778" layer="97" rot="R90">Arduino Pro Mini</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="PRO-MINI-2">
<description>Arduino Pro Mini Layout 2
Sparkfun.com</description>
<gates>
<gate name="G$1" symbol="PRO-MINI-2" x="2.54" y="0"/>
</gates>
<devices>
<device name="" package="PRO-MINI-2">
<connects>
<connect gate="G$1" pin="A0" pad="A0"/>
<connect gate="G$1" pin="A1" pad="A1"/>
<connect gate="G$1" pin="A2" pad="A2"/>
<connect gate="G$1" pin="A3" pad="A3"/>
<connect gate="G$1" pin="A4" pad="A4"/>
<connect gate="G$1" pin="A5" pad="A5"/>
<connect gate="G$1" pin="A6" pad="A6"/>
<connect gate="G$1" pin="A7" pad="A7"/>
<connect gate="G$1" pin="D10" pad="D10"/>
<connect gate="G$1" pin="D11" pad="D11"/>
<connect gate="G$1" pin="D12" pad="D12"/>
<connect gate="G$1" pin="D13" pad="D13"/>
<connect gate="G$1" pin="D2" pad="D2"/>
<connect gate="G$1" pin="D3" pad="D3"/>
<connect gate="G$1" pin="D4" pad="D4"/>
<connect gate="G$1" pin="D5" pad="D5"/>
<connect gate="G$1" pin="D6" pad="D6"/>
<connect gate="G$1" pin="D7" pad="D7"/>
<connect gate="G$1" pin="D8" pad="D8"/>
<connect gate="G$1" pin="D9" pad="D9"/>
<connect gate="G$1" pin="DTR" pad="DTR"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND2" pad="GND1"/>
<connect gate="G$1" pin="GND3" pad="GND2"/>
<connect gate="G$1" pin="GND4" pad="GND3"/>
<connect gate="G$1" pin="RAW" pad="RAW"/>
<connect gate="G$1" pin="RST" pad="RST"/>
<connect gate="G$1" pin="RST1" pad="RST1"/>
<connect gate="G$1" pin="RX1" pad="RX1"/>
<connect gate="G$1" pin="RX1-1" pad="RX1-1"/>
<connect gate="G$1" pin="TX0" pad="TX0"/>
<connect gate="G$1" pin="TX0-1" pad="TX0-1"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
<connect gate="G$1" pin="VCC1" pad="VCC1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" deviceset="A3L-LOC" device=""/>
<part name="U$1" library="Arduino-clone" deviceset="PRO-MINI-2" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="U$1" gate="G$1" x="68.58" y="68.58"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
