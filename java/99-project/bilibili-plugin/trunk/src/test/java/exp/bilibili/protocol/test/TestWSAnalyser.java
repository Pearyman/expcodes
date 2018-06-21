package exp.bilibili.protocol.test;

import exp.libs.utils.num.BODHUtils;
import exp.libs.utils.other.StrUtils;

/**
 * <PRE>
 * 测试WebSocket的接收报文
 * </PRE>
 * <B>PROJECT：</B> bilibili-plugin
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2017-12-17
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class TestWSAnalyser {

	public static void main(String[] args) {
		String hex = "000001080010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C383339333539383134372C302C223330623765353934222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B3332353937343431352C22E4BA86E5A5BDE5A4AAE698AFE79C9FE88E89E8909DE788B1222C302C312C312C223130303030222C312C22225D2C5B31352C225A7A6D222C22466972656C6F6C69222C313131312C31363734363136322C22225D2C5B32342C302C353830353739302C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000005970010000000000005000000007B22636D64223A2253454E445F47494654222C2264617461223A7B22676966744E616D65223A225C75386661335C7536373631222C226E756D223A322C22756E616D65223A225C75393633665C75353932375C7536373238222C2266616365223A22687474703A2F2F69302E6864736C622E636F6D2F6266732F666163652F363538653366323066396263356663393032306433343365326134303934393763303335313764382E6A7067222C2267756172645F6C6576656C223A302C2272636F7374223A3130303239353239322C22756964223A3634353639342C22746F705F6C697374223A5B7B22756964223A393336333531302C22756E616D65223A225C75346530645C75353932615C75373531635C75353437335C75373638345C7539386365222C2266616365223A22687474703A2F2F69322E6864736C622E636F6D2F6266732F666163652F663763636364633963323063373266646536383835393037363062626336643230383234333032382E6A7067222C2272616E6B223A312C2273636F7265223A33313839373730302C2267756172645F6C6576656C223A312C22697353656C66223A307D2C7B22756964223A31313035363435352C22756E616D65223A225C75346665655C75346564395C75373638345C75373963336B6B222C2266616365223A22687474703A2F2F69312E6864736C622E636F6D2F6266732F666163652F623966323635343635323265393836306337383333663635396166336165613431306538363838622E6A7067222C2272616E6B223A322C2273636F7265223A31313235333030302C2267756172645F6C6576656C223A332C22697353656C66223A307D2C7B22756964223A393133363233382C22756E616D65223A225C75383239645C75353865625C75353936355C75353232395C75353936355C75363262395C75383333365C7535333737222C2266616365223A22687474703A2F2F69322E6864736C622E636F6D2F6266732F666163652F343462376637323233623437333462373366626263376462383866363064636265646339656336342E6A7067222C2272616E6B223A332C2273636F7265223A31303136393139382C2267756172645F6C6576656C223A332C22697353656C66223A307D5D2C2274696D657374616D70223A313532393539343730312C22676966744964223A312C226769667454797065223A302C22616374696F6E223A225C75353538325C7539386466222C227375706572223A302C2273757065725F676966745F6E756D223A302C227072696365223A3130302C22726E64223A2237463744344331442D443430332D343134392D414646452D373144434344393943393133222C226E65774D6564616C223A302C226E65775469746C65223A302C226D6564616C223A5B5D2C227469746C65223A22222C22626561744964223A22222C2262697A5F736F75726365223A226C697665222C226D65746164617461223A22222C2272656D61696E223A302C22676F6C64223A302C2273696C766572223A302C226576656E7453636F7265223A302C226576656E744E756D223A302C22736D616C6C74765F6D7367223A5B5D2C227370656369616C47696674223A6E756C6C2C226E6F746963655F6D7367223A5B5D2C2263617073756C65223A7B22636F6C6F7266756C223A7B22636F696E223A302C226368616E6765223A302C2270726F6772657373223A7B226E6F77223A302C226D6178223A353030307D7D2C226E6F726D616C223A7B22636F696E223A302C226368616E6765223A302C2270726F6772657373223A7B226E6F77223A302C226D6178223A31303030307D7D2C226D6F7665223A317D2C22616464466F6C6C6F77223A302C226566666563745F626C6F636B223A312C22636F696E5F74797065223A2273696C766572222C22746F74616C5F636F696E223A3230307D7D000001160010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C383538343635353934372C302C223838613961396132222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B383939373038392C22E99D92E698A52DE59682E68E89222C302C312C312C223130303030222C312C22225D2C5B31382C22E794B5E99FB3222C2233E58FB7E79BB4E692ADE997B4222C332C31363735323434352C22225D2C5B34372C302C31363734363136322C343135315D2C5B227469746C652D38392D31222C227469746C652D38392D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000000E80010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2231353239353839383433222C302C223330326162663230222C305D2C22E59388E59388E59388E59388E59388E59388E59388E59388E59388E59388222C5B31353332383936382C22E9A38EE890BDE68385E99BA8222C302C302C302C223130303030222C312C22225D2C5B5D2C5B31312C302C363430363233342C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001430010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C383035393333383938332C302C223564393064383530222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B31323032373038362C22E59CA8E5A4A9E58FB0E79C8BE7ACA8E78CAAE8B7B3E79A84E7A59EE788B6222C302C312C312C223130303030222C312C22225D2C5B342C22E6A188E58685E68980222C22E59CA8E5A4A9E58FB0E79C8BE7ACA8E78CAAE8B7B3E79A84E7A59EE788B6222C22323638333634222C363430363233342C22225D2C5B34372C302C31363734363136322C343039305D2C5B227469746C652D3132352D31222C227469746C652D3132352D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000012B0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C313535313533303039312C302C226535616366346436222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B363531303036302C22E78CABE5B08FE799BDE5BE88E799BD222C302C312C312C223130303030222C312C22225D2C5B31332C22E4B889E7BAA7E5A4B4222C22E79B94E79B94E5A5B6E59392E59392222C223130333238353936222C31363734363136322C22225D2C5B32392C302C353830353739302C223E3530303030225D2C5B227469746C652D3134342D31222C227469746C652D3134342D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001110010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C333934333131363938362C302C226435613338613865222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B32323934373334362C22554D494E4E4945373939222C302C312C312C223130303030222C312C22225D2C5B31392C22E79AAEE79A87222C224F6C64426131222C3532392C31363735323434352C22225D2C5B35302C302C31363734363136322C313130375D2C5B227469746C652D3133312D32222C227469746C652D3133312D32225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000012A0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C3831333238313732372C302C226462333662396636222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B383038313532362C22E4BD8FE59CA8E4BDA0E5BF83E9878CE79A84E7B4A2E7BD97E696B9E696AF222C302C312C312C223130303030222C312C22225D2C5B31372C22E695B2E587B6E79A84222C22E88B8FE4B9946F5F6F222C3433382C31363735323434352C22225D2C5B34312C302C31363734363136322C31313938345D2C5B227469746C652D3132382D32222C227469746C652D3132382D32225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001250010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C353839393236303038312C302C223037616561646530222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B31313738333135322C22E4B88DE8A681E59083E59296E596B1222C302C312C312C223130303030222C312C22225D2C5B332C22E585ADE799BEE4B887222C22E29885E291A5E6AAA4E8BDAEE59BACE29885222C223136343035222C363430363233342C22225D2C5B35302C302C31363734363136322C313137365D2C5B227469746C652D39352D32222C227469746C652D39352D32225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000011A0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2231353239353733303837222C302C226236616666633039222C305D2C22E59388E59388E59388E5958AE59388E59388222C5B3331333239343939382C22E68891E69C89E586B0E99894E890BDE4BDA0E69C89E5989B222C302C302C302C223130303030222C312C22225D2C5B352C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C353830353739302C22225D2C5B31302C302C393836383935302C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000000E70010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C353433393835333930352C302C223062333535383166222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B313434343131362C225368616161616C6565222C302C312C312C223130303030222C312C22225D2C5B5D2C5B34362C302C31363734363136322C343930325D2C5B226D61792D68696768222C227469746C652D33342D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001360010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C333830333638343738352C302C223463613162366563222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B38313236333938322C22E9AA91E585B1E4BAABE58D95E8BDA6E79A84E99BAAE7B395222C302C312C312C223130303030222C312C22225D2C5B382C22E58D95E8BDA6E9989F222C22E9AA91E585B1E4BAABE58D95E8BDA6E79A84E99BAAE7B395222C2234333532363239222C353830353739302C22225D2C5B34352C302C31363734363136322C353637365D2C5B227469746C652D35362D31222C227469746C652D35362D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001020010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C313235363239303032332C302C226235333234656534222C305D2C22E597AFE38082E7BB93E69D9FE4BA86222C5B3235393437393530392C22E5B9BBE5BFBDE99B80E8B783222C302C302C302C223130303030222C312C22225D2C5B312C22E78C9BE6B189222C22E69F90E5B9BBE5909B222C22323731373434222C363430363233342C22225D2C5B31332C302C363430363233342C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001260010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C313034323332373232382C302C223333653838663561222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B33313031353439342C22E6AD90E69BA6E69BA6E69C80E5969CE6ADA1E4BDA0E4BA86222C302C312C312C223130303030222C312C22225D2C5B31352C22E58D81E4BA8CE5B281222C22E58D81E4BA8CE7A4BC222C3633362C31363734363136322C22225D2C5B33352C302C31303531323632352C33383831345D2C5B227469746C652D3134342D31222C227469746C652D3134342D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001290010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C353632363232313131372C302C223734386637626261222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B31323530343939322C22E587B8E69E9CE985B1E985B1E59186E5A4B4E9B985E587B8222C302C312C312C223130303030222C312C22225D2C5B31382C22E4BAB2E587A1E587A1222C22E4BC98E985B1E698AFE592B8E9B1BC222C3239302C31363735323434352C22225D2C5B34392C302C31363734363136322C313739325D2C5B227469746C652D39352D31222C227469746C652D39352D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001270010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2231353239353934333630222C302C223261336331336438222C305D2C22E59388E59388E59388E59388E59388E59388E59388E59388E59388E59388E59388E59388E59388222C5B33393339373830362C22E9ACBCE59387E795A5E795A5E795A5222C302C302C302C223130303030222C312C22225D2C5B31312C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C31303531323632352C22225D2C5B32362C302C353830353739302C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000010C0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C3236323834373438362C302C226337623464663434222C305D2C22E58F96E585B3E4BA86E582BBE5AD90E4B8BBE692AD222C5B343331363234312C22E6A999E69E9CE4B88EE7B1B3222C302C302C302C223130303030222C312C22225D2C5B372C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C353830353739302C22225D2C5B31312C302C363430363233342C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000011D0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C353035353132363633362C302C226263626662323238222C305D2C22E68891E98089E68BA9E78B97E5B8A6222C5B31383332383336322C22E5A2A8E69894E8A880222C302C312C312C223130303030222C312C22225D2C5B31372C22E98791E68888222C22E98791E68888E88DAFE59586E799BDE6ADA2222C3439382C31363735323434352C22225D2C5B33342C302C31303531323632352C34383533335D2C5B227469746C652D3134302D31222C227469746C652D3134302D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000000FE0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2231353239353931313736222C302C226633363665663739222C305D2C22E6B2A1E4BA86222C5B31303836393930322C22E7BB94E691AFE38184222C302C312C302C223130303030222C312C22225D2C5B352C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C353830353739302C22225D2C5B31312C302C363430363233342C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D000001060010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2D3339323637353433312C302C223238353163326664222C305D2C223233333333333333222C5B3134363731373530382C2230305F5F73756E7368696E655F5F3030222C302C302C302C223130303030222C312C22225D2C5B352C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C353830353739302C22225D2C5B31332C302C363430363233342C223E3530303030225D2C5B5D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D0000011B0010000000000005000000007B22696E666F223A5B5B302C312C32352C31363737373231352C313532393539343730312C2D313038313737313631372C302C223232323731633236222C305D2C22E699BAE78684222C5B38383234393333322C22E78BB4E78BB8E78D99E78C81222C302C302C302C223130303030222C312C22225D2C5B342C22E5BFBDE682A0222C22E590B4E7BB87E4BA9AE58887E5A4A7E5BFBDE682A0222C3634372C363430363233342C22225D2C5B31312C302C363430363233342C223E3530303030225D2C5B227469746C652D3134372D31222C227469746C652D3134372D31225D2C302C302C7B22756E616D655F636F6C6F72223A22227D5D2C22636D64223A2244414E4D555F4D5347227D";
		alalyseMsg(hex);
	}
	
	private static void alalyseMsg(String hexMsg) {
		byte[] bytes = BODHUtils.toBytes(hexMsg);
		String msg = new String(bytes);
		System.out.println(StrUtils.view(msg));
		System.out.println("====");
		
		int len = 0;
		do {
			len = getLen(hexMsg);
			if(len <= 32) {
				break;
			}
			String subHexMsg = hexMsg.substring(32, len);
			msg = new String(BODHUtils.toBytes(subHexMsg));
			System.out.println(StrUtils.view(msg));
			
			
			hexMsg = hexMsg.substring(len);
		} while(StrUtils.isNotEmpty(hexMsg));
	}
	
	private static int getLen(String hexMsg) {
		String hexLen = hexMsg.substring(0, 8);	// 消息的前8位是本条消息长度
		long len = BODHUtils.hexToDec(hexLen);
		return (int) (len * 2);
	}
	
}
