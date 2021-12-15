// Copyright (c) 2021 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <gigamonkey/spv.hpp>
#include <gigamonkey/script/pattern.hpp>
#include "gtest/gtest.h"
#include <gigamonkey/boost/boost.hpp>

namespace Gigamonkey::Bitcoin {

    // can result in stack smashing
    TEST(TransactionTest, TestTransaction) {

        string tx_hex = string{} + 
        "0100000001DB78AC273A4113615B5FC2D5BC24904884988201A7DB977FEEE56F73F5BF718CB00000006A4730440220295348C95DBAA2E0CF67F2EDA2A442AFF7D6D8DCA2" + 
        "765D0D5CD11D8D3F0B75800220711DA79E4BE13BDD54DBCD3C5CFAD5F4C9E4F709BDF6B93DB8E94E464BFAE8EC412102A97974AC47721DF4B4D34DAAF277E015B29D377A" + 
        "90E546C442F9A32E4438CF61FFFFFFFF6E0000000000000000FDDA0E006A0A22686D7779646122202D20686F77206D75636820776F756C6420796F7520646F6E61746520" + 
        "616E6F6E796D6F75736C790A0A686F7720746F20637265617465206F776E65726C657373204254432F4243482F4253562061646472657373207769746820737065636961" + 
        "6C206D65616E696E670A0A616D6E6573696140616D6E657369613A7E240A616D6E6573696140616D6E657369613A7E242077676574202D2D71756965742068747470733A" + 
        "2F2F6769746875622E636F6D2F6C6962626974636F696E2F6C6962626974636F696E2D6578706C6F7265722F72656C65617365732F646F776E6C6F61642F76332E322E30" + 
        "2F62782D6C696E75782D7836342D7172636F64650A616D6E6573696140616D6E657369613A7E242077676574202D2D71756965742068747470733A2F2F6769746875622E" + 
        "636F6D2F736970612F6265636833322F7261772F6D61737465722F7265662F707974686F6E2F7365677769745F616464722E70790A616D6E6573696140616D6E65736961" + 
        "3A7E242077676574202D2D71756965742068747470733A2F2F6769746875622E636F6D2F6F736B796B2F63617368616464726573732F617263686976652F312E302E352E" + 
        "7461722E677A0A616D6E6573696140616D6E657369613A7E24206C73202D6C2062782D6C696E75782D7836342D7172636F6465207365677769745F616464722E70792031" + 
        "2E302E352E7461722E677A0A2D72772D722D2D722D2D203120616D6E6573696120616D6E657369612020202036343934204175672031322031343A313420312E302E352E" + 
        "7461722E677A0A2D72772D722D2D722D2D203120616D6E6573696120616D6E657369612035303337373638204D61792032362020323031372062782D6C696E75782D7836" + 
        "342D7172636F64650A2D72772D722D2D722D2D203120616D6E6573696120616D6E657369612020202034333736204175672031322031343A3133207365677769745F6164" + 
        "64722E70790A616D6E6573696140616D6E657369613A7E242074617220786620312E302E352E7461722E677A0A616D6E6573696140616D6E657369613A7E242063686D6F" + 
        "64202B782062782D6C696E75782D7836342D7172636F64650A616D6E6573696140616D6E657369613A7E2420616C6961732062783D2F686F6D652F616D6E657369612F62" + 
        "782D6C696E75782D7836342D7172636F64650A616D6E6573696140616D6E657369613A7E240A0A31292042617365353820616464726573732069732076616C696420666F" + 
        "7220616C6C204254432F4243482F4253560A0A312E31292062617365353820616464726573732066726F6D20746578740A616D6E6573696140616D6E657369613A7E240A" + 
        "616D6E6573696140616D6E657369613A7E24206278206261736531362D656E636F6465202273656E64203125206F6620686F77206D75636820796F75276420646F6E6174" + 
        "6520666F72207075626C697368696E6720696E20626C6F636B636861696E20646979206D616E75616C20666F72206275696C64696E6720736D61727420726F636B657422" + 
        "207C20627820726970656D64313630207C20627820616464726573732D656E636F64650A314A596D6871733438313252354D65376648554E6F386466637A5A776A793848" + 
        "32640A616D6E6573696140616D6E657369613A7E240A0A312E3229206261736535382061646472657373207769746820746578740A62617365353820616C706861626574" + 
        "203D20646967697473206578636C7564696E6720223022202B206C6F77657263617365206C657474657273206578636C7564696E6720226C22202B207570706572636173" + 
        "65206C657474657273206578636C7564696E67202249222C20224F220A737472696E67206F66203333206C6574746572732C207374617274732077697468202231222C20" + 
        "6C6173742036206F7220372077696C6C206265206368616E6765642C203235206F722032362072656D61696E20666F7220746578740A616D6E6573696140616D6E657369" + 
        "613A7E240A616D6E6573696140616D6E657369613A7E24206278206261736535382D6465636F646520315072636E74486D77796461466F724B694C4C4261644775797878" + 
        "7878787878780A30303034353239316335366333646630666161376435303864313736363037363631383762613432336631343866663731310A616D6E6573696140616D" + 
        "6E657369613A7E240A72656D6F7665203220666972737420616E642038206C61737420616E640A616D6E6573696140616D6E657369613A7E240A616D6E6573696140616D" + 
        "6E657369613A7E2420627820616464726573732D656E636F646520303435323931633536633364663066616137643530386431373636303736363138376261343233660A" + 
        "315072636E74486D77796461466F724B694C4C4261644775797878797336554C790A616D6E6573696140616D6E657369613A7E240A0A3229204254432053656757697420" + 
        "616464726573732028626563683332290A0A322E31292073656777697420616464726573732066726F6D20746578740A616D6E6573696140616D6E657369613A7E240A61" + 
        "6D6E6573696140616D6E657369613A7E24206278206261736531362D656E636F64652027302E30303120686D7779646120666F72207075626C697368696E672070726976" + 
        "61746520696E666F726D6174696F6E2061626F7574206261642067757927207C20627820726970656D643136300A66376261396164613036633833343536306534333963" + 
        "6662336235633035346462313332393134640A616D6E6573696140616D6E657369613A7E240A616D6E6573696140616D6E657369613A7E2420707974686F6E330A3E3E3E" + 
        "0A3E3E3E2066726F6D207365677769745F6164647220696D706F727420656E636F64650A3E3E3E0A3E3E3E207072696E7428656E636F646528276263272C20302C206279" + 
        "746561727261792E66726F6D686578282766376261396164613036633833343536306534333963666233623563303534646231333239313464272929290A626331713737" + 
        "6166346B73786571363976726A726E6E616E6B687139666B636E3979326437683071337A0A3E3E3E0A0A322E322920736567776974206164647265737320776974682074" + 
        "6578740A62656368333220616C706861626574203D20646967697473206578636C7564696E6720223122202B206C6F77657263617365206C657474657273206578636C75" + 
        "64696E67202262222C202269222C20226F220A737472696E67206F66203332206F72203531206C6574746572730A3E3E3E0A3E3E3E2066726F6D207365677769745F6164" + 
        "647220696D706F727420434841525345542C20636F6E76657274626974732C20656E636F64650A3E3E3E0A3E3E3E206172726179203D205B434841525345542E66696E64" + 
        "28782920666F72207820696E20277065726D796C686D7779646173656E646472306E656D73677430366164677579275D0A3E3E3E207072696E7428656E636F6465282762" + 
        "63272C20302C20636F6E76657274626974732861727261792C20352C20382929290A626331717065726D796C686D7779646173656E646472306E656D7367743036616467" + 
        "757972666632797A0A3E3E3E0A3E3E3E206172726179203D205B434841525345542E66696E6428782920666F72207820696E2027306E65706572636E74686D7779646166" + 
        "3072643078796E677768307730726B7368656C70737072307465637473366164677579275D0A3E3E3E207072696E7428656E636F646528276263272C20302C20636F6E76" + 
        "657274626974732861727261792C20352C20382929290A62633171306E65706572636E74686D77796461663072643078796E677768307730726B7368656C707370723074" + 
        "656374733661646775797163357873637A0A3E3E3E0A3E3E3E206578697428290A616D6E6573696140616D6E657369613A7E240A0A332920424348206E65772061646472" + 
        "65737320666F726D61742028616C736F20626563683332290A0A332E31292042434820616464726573732066726F6D2074657874202D20636F6E766572742066726F6D20" + 
        "312E310A616D6E6573696140616D6E657369613A7E240A616D6E6573696140616D6E657369613A7E242063642063617368616464726573732D312E302E352F0A616D6E65" + 
        "73696140616D6E657369613A7E2F63617368616464726573732D312E302E35240A616D6E6573696140616D6E657369613A7E2F63617368616464726573732D312E302E35" + 
        "2420707974686F6E330A3E3E3E0A3E3E3E2066726F6D2063617368616464726573732E636F6E7665727420696D706F727420746F5F636173685F616464726573730A3E3E" + 
        "3E0A3E3E3E207072696E7428746F5F636173685F616464726573732827314A596D6871733438313252354D65376648554E6F386466637A5A776A79384832642729290A62" + 
        "6974636F696E636173683A71727138636B646461367274686B7835786639616D3271637A6637617679666766676A6A3668653032340A3E3E3E0A0A332E32292042434820" + 
        "61646472657373207769746820746578740A62656368333220616C7068616265742073656520322E320A737472696E67206F66203334206C6574746572732C2073746172" + 
        "7473207769746820227171222C20656E64732077697468202271222C2033312072656D61696E20666F7220746578740A3E3E3E0A3E3E3E2066726F6D2063617368616464" + 
        "726573732E63727970746F20696D706F7274206233326465636F64652C20623332656E636F64652C2063616C63756C6174655F636865636B73756D0A3E3E3E0A3E3E3E20" + 
        "707265666978203D2027626974636F696E63617368270A3E3E3E206172726179203D206233326465636F6465282771717065726D796C686D777964616630723675726E36" + 
        "61646775797368307573657127290A3E3E3E20636865636B73756D203D2063616C63756C6174655F636865636B73756D287072656669782C206172726179290A3E3E3E20" + 
        "7072696E7428707265666978202B20273A27202B20623332656E636F6465286172726179202B20636865636B73756D29290A626974636F696E636173683A71717065726D" + 
        "796C686D777964616630723675726E366164677579736830757365716C63787A6E3071370A3E3E3E0A3E3E3E206578697428290A616D6E6573696140616D6E657369613A" + 
        "7E2F63617368616464726573732D312E302E35240A0A23020000000000001976A91403B7892656A4C3DF81B2F3E974F8E5ED2DC78DEE88AC23020000000000001976A914" + 
        "075B7DFCA1465DAA6F51B8497AF83C10042EF39988AC23020000000000001976A91408D2DE7257E4F777653B939C6BCB7401AEABF1FF88AC23020000000000001976A914" + 
        "04D9D15E67E6F20551992E03039711E59281F72888AC23020000000000001976A91406F61B94F0E562E41E7137A8B0AA78DB6102925788AC23020000000000001976A914" + 
        "09CC4CB806F792FE235C1B8149C0267B12067C9788AC23020000000000001976A9140A9598557E4075D6543A51A33A6A84D6945B6A8E88AC23020000000000001976A914" + 
        "858BCAD4B16B4D71E42583496A2E152BD5C53D0B88AC23020000000000001976A914BE85D05E29583DFEF599C4CCCF5E29A38971458F88AC23020000000000001976A914" + 
        "78BA86C946A25A01FCE6A7B6734F99892A00A9F388AC23020000000000001976A914C728FE716A82F3E513BA5CA8E3056ADE5C56070988AC23020000000000001976A914" + 
        "FAF13C7A6B1F9E6F064812C8AF96A0B53519B67388AC23020000000000001976A9141EF47DCE94094E0FAE1E4DFB1C1ABEEF8639C09988AC23020000000000001976A914" + 
        "1A6C3CBA5975DF50D416477927E255209661C10388AC23020000000000001976A914EA7540961D17E138986DED210E09DEB680F89E4B88AC23020000000000001976A914" + 
        "2D803E6AD19EA6516C9685B261076E6F3172BBBE88AC23020000000000001976A91444179DC3E751CB0A62169117D5CC3404C742011688AC23020000000000001976A914" + 
        "4A5FA1E5E423D9B0B0F8E6603117F24584427B7788AC23020000000000001976A91421F74480F59A99C25026A7A322F7300C188176E088AC23020000000000001976A914" + 
        "E792349AE30166B5D0D434AC13EAE5498FCFD95588AC23020000000000001976A9145A9BB733B8BBE6296C59B5585BCB57243A5E918488AC23020000000000001976A914" + 
        "EDE03320A2DCA42E7A301D759D7BF78729D944E188AC23020000000000001976A914971415E715E8DE8FE848156B6FB8FB12B751356A88AC23020000000000001976A914" + 
        "E15A983D92F5D4957DF1D1676F316FF5FD350CA488AC23020000000000001976A914E748BC738BB637802839F65795B82593EAC5931288AC23020000000000001976A914" + 
        "17E445B47CF02F0298E6D4171D7468F1F62CD58B88AC23020000000000001976A9145345667FA8D1AEC205C4BB7EE721AAFECA454C1988AC23020000000000001976A914" + 
        "4F8D72D65AC474B237C5A0DA02198A940E9E418E88AC23020000000000001976A914064978BD0956501F022C88A8DC14F95EBE3311B888AC23020000000000001976A914" + 
        "3B85AA69A9DE41ADC6ECD1568E6CB9514A01E16688AC23020000000000001976A9141688D860148A224AD738CA702F60D810164E952888AC23020000000000001976A914" + 
        "A629F4074CE0E4E12D99E387B0E05C1F45124CB688AC23020000000000001976A9140A93802C925565CECD03CC1CD2B5AD89942A6B3188AC23020000000000001976A914" + 
        "4C6C374E99668E1D8981D8DAE70BFA6E51D82FB188AC23020000000000001976A914C0818607A96E3FA026719D26816BBC6EAC4B827C88AC23020000000000001976A914" + 
        "164173A0BBFA31046D12BFB9FAD0F8F24746616388AC23020000000000001976A914E9D00DEC2E8E265E66C5A58AB8D73F507C8D10F488AC23020000000000001976A914" + 
        "AE9E288B12A60B31A891384FD3D7041CF3B6E74588AC23020000000000001976A914F0AFB4AD8AFE420C06EAAF7F2CEA1028103EF2DB88AC23020000000000001976A914" + 
        "7E8B8242BAE3BE4752759F9DCF29DFEA42A11FFB88AC23020000000000001976A914340CFCFFE029E6935F4E4E5839A2FF5F29C7A57188AC23020000000000001976A914" +  
        "C230129FBB973E8040113293152BD54794B4199D88AC23020000000000001976A914BE8173FA5E6A2A8FE9DAE87049200A5D3D88562188AC23020000000000001976A914" + 
        "C69163CECAD874DFD04FB23B080746EDB4C2568B88AC23020000000000001976A914B8654228AB79E7C6F38DCE505A1BE3075606AF6E88AC23020000000000001976A914" + 
        "B9A564E26543BD66EE6738B5B4D9F5D2D1D2852788AC23020000000000001976A914652C9C52ACF6493E17A655C2ECD07300685F4E6B88AC23020000000000001976A914" + 
        "01702974C65369C609D3B35255434706A22902E188AC23020000000000001976A914BDD3E671D87CE62BAD69F123A29B112570BEA72488AC23020000000000001976A914" + 
        "85BA2A0C46A686E4808AA55E43306DA60028749688AC23020000000000001976A91451436BE6DEFFAC5B29A3B54F4935440C19BBB44A88AC23020000000000001976A914" + 
        "EF5A9A06D2B215399589A8E7821F31BC7DC344C188AC23020000000000001976A914E3B8591E6B015C7684AF698A28D96D1A3E475B7A88AC23020000000000001976A914" + 
        "BA7F10AD717D894EC75910EF87B6F3FD5DFB220488AC23020000000000001976A9145614EC44C84339E4A8FA044D4A2FC18C07D7743B88AC23020000000000001976A914" + 
        "73795471CCFDDEF9867F41AE207CCF86C76F458288AC23020000000000001976A9143D76B2E081A774F8EC337436391A4C8055E92E0688AC23020000000000001976A914" + 
        "D049E00F7350D232AF8B907D300AC702E5DADBD188AC23020000000000001976A9148B47868DFEF2A41942DAEB409E6A45B15F6E693F88AC23020000000000001976A914" + 
        "3B829899F2333968CE9E7BCE8DF557FDF88BDF5F88AC23020000000000001976A914C20A7136BA44CFDFC758F375EF0A3DA4CECFF46188AC23020000000000001976A914" + 
        "7776C649EEE08056264D31EF350D39C6A6ACC62888AC23020000000000001976A914BF6E6032D05A788B16B130CC3F79AC04082DE37988AC23020000000000001976A914" + 
        "A5E669661DFA273F7BEE99C81BD3F8089ED7B0A688AC23020000000000001976A9147AB72DF23957455D88B99DD0AC56BE2E0666C14A88AC23020000000000001976A914" + 
        "EE3C2C903BF6092F7BA5D8139288EE15B34EBD7688AC23020000000000001976A914BED7447DABB27D54313C049739D1C73BAB42C67D88AC23020000000000001976A914" + 
        "70DE1882B67F68A1209EE04B3B3268D0055122E788AC23020000000000001976A914C43A71226F6CA844C39F64F3321FCB30CC8FF1F988AC23020000000000001976A914" + 
        "6C8E4DD8719473743F840007EACBC1059B8CE79988AC23020000000000001976A91405183076B66CB797312F2076FA0A0AA95E5D8C7988AC23020000000000001976A914" + 
        "05070D19A22991E762F8C46C1EAA45660445B70888AC23020000000000001976A914FD471D4643E9BED19915815F6EED309F1DDB2F3E88AC23020000000000001976A914" +
        "43CF755DE8AB8A8A05590E9709849644E9C587A288AC23020000000000001976A914D2563583E740E2648C11B8BBFD1747BD1AF429B288AC23020000000000001976A914" + 
        "10875BA01A898A59B1DFC75E4D37E9FE7FD8128E88AC23020000000000001976A9149B3819CF2CCF06E7EEA62F81E628790419E80ECB88AC23020000000000001976A914" + 
        "419939054E603DA3F2A3A51A8D78492127872BFB88AC23020000000000001976A91443C0A887E545114AD902A6EFE2CB1EB23BDBBEE588AC23020000000000001976A914" + 
        "98F564DA39028E64DF3E157669F9CDB7158ECA8788AC23020000000000001976A914DE808452D515E1AAB782EC759C05C67143D8A87488AC23020000000000001976A914" + 
        "1BD5159E6F5FF2F1B8672C056FA03DC0F50948D088AC23020000000000001976A9144ADD02E1CAB65B95B931F02E0D4FF55826F2A91588AC23020000000000001976A914" + 
        "DA705A34B85B23804887813EEAD45C4A1EE3537B88AC23020000000000001976A914EE022053B593AD4D69CB5D2623D4CD8011F626B088AC23020000000000001976A914" + 
        "E7786CA96644FC3294EDE8F898465D39EFFE14CC88AC23020000000000001976A9145DF4C1461B731B52E34F4FCEB39159480F690F8988AC23020000000000001976A914" + 
        "B179F8B8B04A906A23CAFB0264D97B405CF8A20488AC23020000000000001976A914EC9765CBA8EADAFE4E60F6F671471A1ADC20541188AC23020000000000001976A914" + 
        "7A5869AA97FB5AD993B712FED79346390877A6D588AC23020000000000001976A91430BBD6A1475A25F925BAFAC545F1F309E520201188AC23020000000000001976A914" +
        "0C11E0AF648C09E5EBB87C102B87FAA97F2B5D3188AC23020000000000001976A91479179214336C6439E6CE9084D92E584BE2170DCD88AC23020000000000001976A914" +
        "FA15440F78605E712B5544695F89F7A3AC718E0388AC23020000000000001976A914CA3FBD84606E6585FAF3C04C0D968EE2BACB18BB88AC23020000000000001976A914" +
        "988E346F9CC4AD23C4CAE85EE053D0CCAB8FDB7188AC23020000000000001976A9146A488D87573769BBFE0A514B7A58932AAB48BCA188AC23020000000000001976A914" +
        "946A23944EB147590794D582C9652700D3A674E088AC23020000000000001976A9142A596A2C686D7F4E0E30A1BD940A829464A734F188AC23020000000000001976A914" +
        "4DC29FDF91755087638CCF290F49D21FC412755088AC23020000000000001976A914BA40E4DEB205BB8ECBEE9C495D219ED2945E02A988AC23020000000000001976A914" +
        "9967FE4A31044F31122E93F2C6279EC2CA04797788AC23020000000000001976A914D1A8FBF4B187CC45ADCE3BB302C90EA0B8C4A9DD88AC23020000000000001976A914" +
        "99B614D3BE932141D29A6CEE876742BB3B06984F88AC23020000000000001976A91483EE0D5123317182711D761FA5C504404141729F88AC23020000000000001976A914" +
        "BFF42E6E53F3031AED7A85E2C69D1B029969074A88AC23020000000000001976A914C08965F6944CAC349AA27F1125A6C2F5D9DA2A1588AC23020000000000001976A914" +
        "714B401DAD2D9D4F2D127A990A38962A9BC4FD5688AC17D7FC08000000001976A9145773F7E192A69985C4EFAEA268C1D27BD089D58B88AC00000000";
        
        ptr<bytes> tx = encoding::hex::read(tx_hex);
        
        ASSERT_NE(tx, nullptr);
        
        EXPECT_EQ(tx->size(), 7676);
        
        EXPECT_EQ(Hash256(*tx), digest256{"0x0473718d87e0bd19437d19da0454873c074d5c9698d9e6e41b0c5cae2dcbe202"});
        
        transaction t = transaction{*tx};
        
        EXPECT_TRUE(t.valid());
        
        EXPECT_EQ(t.Version, 1);
        
        EXPECT_EQ(t.Inputs.size(), 1);
        
        EXPECT_EQ(t.Outputs.size(), 110);
        
        EXPECT_EQ(t.Locktime, 0);
        
        EXPECT_EQ(t.serialized_size(), 7676);
        
        EXPECT_FALSE(Bitcoin::pay_to_address{t.Outputs.first().Script}.valid());
        
        EXPECT_EQ(bytes(t), *tx);
        
    }
}
