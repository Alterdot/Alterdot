// Copyright (c) 2014-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <crypto/aes.h>
#include <crypto/poly1305.h>
#include <crypto/ripemd160.h>
#include <crypto/sha1.h>
#include <crypto/sha256.h>
#include <crypto/sha512.h>
#include <crypto/hmac_sha256.h>
#include <crypto/hmac_sha512.h>
#include <random.h>
#include <utilstrencodings.h>
#include <test/test_alterdot.h>

#include <vector>

#include <boost/test/unit_test.hpp>
#include <openssl/aes.h>
#include <openssl/evp.h>

BOOST_FIXTURE_TEST_SUITE(cn_tests, BasicTestingSetup)


static void TestCnHash(int hashSelection, const std::string& input, const std::string& desired)
{
    uint512 inUint  = uint512S(input.c_str());
    //uint512 outUint = uint512S(desired.c_str());
    
    uint512 result;
    cnHash(&inUint, &result, 64, hashSelection);

    std::string actual = result.ToString();
    BOOST_CHECK(actual == desired);
}

BOOST_AUTO_TEST_CASE(cryptonight_dark_hash) {
    TestCnHash(0, "0dd2aab67e4594ec89125800e8ffa008528952449dcf90487fae8393e52e3c552e9eae33229ce1fefabf1fea634f7ca3cda5481ce972db121da1209184454eaf",
                  "00000000000000000000000000000000000000000000000000000000000000009ba78b33e354a0a1d85c8bd1c25c8a97805d23dd4826d7368a045debbce48bae");
    TestCnHash(0, "0dd2aab67e4594ec89125800e8ffa008528952449dcf90487fae8393e52e3c552e9eae33229ce1fefabf1fea634f7ca3cda5481ce972db121da1209184454eaf",
                  "00000000000000000000000000000000000000000000000000000000000000009ba78b33e354a0a1d85c8bd1c25c8a97805d23dd4826d7368a045debbce48bae");
    TestCnHash(0, "1ce5d3199b92c64c35382e15b602d47c4965640ca4bf425b7b5ce560121cfdf3747432c17a501d20ce86b30fc1518ec1dc5f0002deede0dd56d3c0575027ee4b",
                  "0000000000000000000000000000000000000000000000000000000000000000c57b8ea3130ac46dafbddb85049597d9c029586cac23865d63583a10db0dc75b");
    TestCnHash(0, "3fe59f575c5a6ee9eba9dc9ed15b8998ad823fc5b8462f77fa4c500d1f02452728284993f80d49e7db80a7518364bd1d76cefc7306ad8da08a4c731f9edcac67",
                  "0000000000000000000000000000000000000000000000000000000000000000001adbe9f62c9d73d9da2a1454625c7adb96e4dd60a7a89bef40f4b058dea34f");
    TestCnHash(0, "79c6cb9cdf6eb7a7b626cea759bb5a2aa35aaf75177387030cf0244a0bcd3b65cc7325c088cbc126bb8537f5bed658365f39bf6aafedb0d18073a03d4b0e43b6",
                  "0000000000000000000000000000000000000000000000000000000000000000b3d368f9e13e6508b838570908638a64e915a04dab64d5ed9ba242865910aff0");
    TestCnHash(0, "a2d22cd28d2e057465bec460b07ef3d9e3837efc691b3660a5686bd2c1a8ccd910c40a11f6d514ec5b92b854f99f02aeb74b4190ca5b46fb68c836e475e11f6c",
                  "0000000000000000000000000000000000000000000000000000000000000000676f640e904c9362564d8ea6aed7f0d010871f72dbb77a2de2ee032f4929306d");
    TestCnHash(0, "ad060617457b51efbb8e892c1f0ac241d29d19f7289ebde7e6be5fb2f130827971829fa488c4693e735bb9c7eaf05cd07482679d4ddfee5a53dc906e37aa872e",
                  "0000000000000000000000000000000000000000000000000000000000000000b1bdc3a4b495baa8b76c10cbab070a30e982b0164653f228f0fab7779e76c2a9");
    TestCnHash(0, "c34ef8e39d498902e169776b10f419bb09f352b7b951df1b4c3dca0725371cbbc20195c1fd56025030627692d81b45c2d33d28c7dc7952a9ae02496b3694c28d",
                  "0000000000000000000000000000000000000000000000000000000000000000000fa116aa830aca800b3df16b5b2ab52de8e296c56f1f0c206fcc4c6b9fd653");
    TestCnHash(0, "c46373f01ec0100e196399841db662930a420840f6f2dd8750a5d7e9f685f02af45c91aa2b0f5c8f5b0fa1ecd5c19b09b13144999a0eb3f6812ce1669b0bfd68",
                  "00000000000000000000000000000000000000000000000000000000000000008c260921b9580e3c9ef706d6da7d1f0a317acf0c3699bab28f7c62186a1db1c5");
    TestCnHash(0, "e7ccd50d120b6906f56c9849b9968e39aa7f4fb39b6e2598d52bde74fed13883197f2e0eae2d6eef67ba637e0168f088c624ee5958c72d71863d28b59cc49256",
                  "00000000000000000000000000000000000000000000000000000000000000000001ed8805fb5800e2ea6ad3fcb2509c1bb5f5fbb1e97f0c759b64fd8cc3f649");
    TestCnHash(0, "e96b3be54a91c25a81dbf5c5b0ad69a935e072420a9e2b198bbfdaf64a4cb3aa61004aa2ac955961e33023800c9411e945dca8a8ea0203c9535b8a7d1cfd41c7",
                  "0000000000000000000000000000000000000000000000000000000000000000788ba53b671f6ae85576738d544756b04e327681a9a21fa2bbae64854e28ae5d");
    TestCnHash(0, "f66a1ba8f962b3745c379d0ccd3164b89a01049917449b3c7f7b9bc12dbc36c941c9abbb4a39935e14c47a2aabc6b81ca37885982b54132a2ba91437f3e24e00",
                  "0000000000000000000000000000000000000000000000000000000000000000dbec617302554350e9a1a96fbba758917e2158ee259a4fcbc62e038d34943bef");
}

BOOST_AUTO_TEST_CASE(cryptonight_darklite_hash) {
    TestCnHash(1, "2392a7eee40b2365cf7af938b5baa859555e9d9eb390a0ec649f384e3e985d5a19aecd8b54c5e8be482196e8c81383afd93ac31c41164495d3a3d6a112b51018",
                  "0000000000000000000000000000000000000000000000000000000000000000eef4993f6b295d9ad661bb6f3f3ae58c6950e4bebb37e5eeba74830cf161da66");
    TestCnHash(1, "248fe41b295eb84a94eaffbc3803126995e4ab9b382a8711525d01e1f88cd1c6b3902065c98f5385e23b11c87face2f88026ae81ea8c4597f53dfa5fb329ffa2",
                  "0000000000000000000000000000000000000000000000000000000000000000001ae58d983a5249846649d36d1cad00b5b08f5fd14cb21e83146ee038b524a8");
    TestCnHash(1, "27290002856770b7fe8585370efbc0221b53fc377f19dc30dfed5dad960d8a186363c23651e6473e4c20bee3c22bf87d24557d3fea0685e815724349f13a3ea4",
                  "00000000000000000000000000000000000000000000000000000000000000000004b524f553e3a6e352aff7a1e2858250ac3b455755344b2c3dfe795eaecbe6");
    TestCnHash(1, "3a59528c7cf3f517cc886440dd0c61ea575483a7038a7e17ad255ce730035120a1d9ebe6876eb9903a4e018f06f2157b97d0f3bb982cd6687d991f038df3d950",
                  "00000000000000000000000000000000000000000000000000000000000000000003bc3cc19384fbfc0121f1416a7f301835231c77ca8090686b72e3f190e1b9");
    TestCnHash(1, "3d57fb6da5bdec53cbc3c58e7f9c91308cf0c898f054f1e64e64f5d1581872213e59cce197624940bf8af751ced69dd8fa82500f6cd2a259e0dedcded2aa78b3",
                  "000000000000000000000000000000000000000000000000000000000000000000166e792f566e19ffec7389faf3aff79ab92e834412900486123a136d469217");
    TestCnHash(1, "404292722772134671f68dcafcb1e9b941cbb2e95d6b2a41094f876926fc299ba7031570ff544a192e357a928126bb9b4948b70305c166dbbdae52e61b33c124",
                  "000000000000000000000000000000000000000000000000000000000000000089d775d8737882add2e34239c893606d843105531f07e639f0902bffd1d72a34");
    TestCnHash(1, "502b7007273fee44c7eb3dc4f11d2b82ad39bd18f24a4ddccfb39b9fd1e481a7fdd5c0d984e3d7c130e21c9f081bf2c3eb87e6d9aba64fb7ea23ca77a43a0e68",
                  "000000000000000000000000000000000000000000000000000000000000000000142588be37b113857b443aa9d4c5fb129a7f8a912e455df2bf990ede589ee1");
    TestCnHash(1, "5e1d1e8177de542152186de4387ff2a1f02a5bc73932f562cb40b369f44b8e956e7cc717a4cc684fb3e70af5690c64c621c6e3d819baad9b6bdf15847d306591",
                  "0000000000000000000000000000000000000000000000000000000000000000db3b8ae6e884bcc38ef6b0a48d061d393bb6a5b33bb13a9112161853b6faae9c");
    TestCnHash(1, "684d4dc825599a8ed351928615fdbb6cdf4ec94267139766daf273c371e64405508d5a4ab62df1b50b6a91dd20e74b086f7c619c3137ca8d00e92c8cabfaca35",
                  "0000000000000000000000000000000000000000000000000000000000000000f01c7c45a5f9e29fe1e61183552549c88d93937275766d67ef522cefa6815c86");
    TestCnHash(1, "7583fa2cc89f2bccf63bc0cb7b0fe78c6d04aa5cc9a146fffc018d2b07a405a3e8fd22bd39a6cb12dd6281920735bba1e8aa944631a4be9fc72206c5f6280001",
                  "0000000000000000000000000000000000000000000000000000000000000000000099c396200ce6164de4afea0ca0beebc0fd4ad770f9e45a8c23ac39061167");
    TestCnHash(1, "991a814edb1704732b9145babc1a1fb9553ac80404a1db32c1c66ddbc9629372f3a6ea02630c340f19602bfba51388d4ca1b8706b3b22035e2155a5c45850c9d",
                  "0000000000000000000000000000000000000000000000000000000000000000b426640fb9cbf28fa85b352c40bd3c8ecc1b97a645f315a4e5be30ed6a6ed69e");
    TestCnHash(1, "a9e8b394ecb1057129513b03bb92218c6b33d3c2dd9a0e39bc4be6cde9ac74e3c453a53422dca22f057f3b280fdc86ebb5965988f338cf5198948401039ee36a",
                  "0000000000000000000000000000000000000000000000000000000000000000f7e612c63b5b7b8e5ce1966664c9de95951e543c7bbe85974bc1a348a5629e1c");
    TestCnHash(1, "cad06519cbc6da6cb28ea4685aa74f2d680dd88b18250045355e1ea65d922934e0e1a35e0aa28a51491c85e2eac02df4af1a1e923d3a96f5b9b3e69bfff6090b",
                  "00000000000000000000000000000000000000000000000000000000000000001ecc68f1a6d109ed344c8cdee1ec00c3425805bbbbd4ad80a21204accdb82982");
}

BOOST_AUTO_TEST_CASE(cryptonight_cnfast_hash) {
    TestCnHash(2, "1f6801bbd5c890e4c7b6c1a94b2fc0312dd8d545459b6da4ac99808610713950186cd87e1269aa700171f39307db588dd75cd5d4727d851c0569e3d2792a2ec1",
                  "000000000000000000000000000000000000000000000000000000000000000025dcbb730c36f0628fa45bd81914e3473980027bc945c6bba473f662274e3492");
    TestCnHash(2, "4a023d0fa3945ae93640835f9a33829dfab3f8c178f329309d0a5dfb038f3d13261897fdfef478c7d109c84ccb93415652e70392cadab913d07c21b80a5da170",
                  "0000000000000000000000000000000000000000000000000000000000000000984c35c44f248006e3ee4c7e2e01c10abdc2b289da2a4b1e310be4b20e1ec72a");
    TestCnHash(2, "5887f75d10935a8fad4109ac54f11c3f748944a8e599f1e81b9760b8c2fd77e44b87865d85dceee04653612a04c94ec902db37cd28e7ad56f99b7db06d272a8f",
                  "00000000000000000000000000000000000000000000000000000000000000000001439bc850f5d3c5559bea5cf0b5ad23ae2e8fff9c7f4fd101463d380b2f60");
    TestCnHash(2, "62f17d8bbfe205834577711690c269b012477dde4bae2c615543bae5305c0f35b1a36cbe45a460d19912ff02bf10c37715be041b0709711d6ddf3da6c266e014",
                  "000000000000000000000000000000000000000000000000000000000000000000061b716488245fcb6b86add4c1eda696f16e5eca92cb804902d325a70c2b74");
    TestCnHash(2, "8cfb32a83189144d458e07616aebb60c2005b8d1eab2fe9372a19fbb3623f6f5e9a99e0e4d8c530ee3d194f22d26606564aa8f444000f78f50ccfe5e5b4d4e87",
                  "0000000000000000000000000000000000000000000000000000000000000000001fa5ed6f43a68dd2c64bc8fddc02fc51d631bd59d37511d7b79d61f6088423");
    TestCnHash(2, "a47da5b1e2a9ef089390aad35bf3bc7bd2d7a4f896752852efbcd9f53668ed5318e7b837536425f53d0be13c5a4e757ca3998b4c8df864cec082b6b7f6b4e5ff",
                  "0000000000000000000000000000000000000000000000000000000000000000001a7785e8bcc6d521ac1b5cbf9ca5ab92aae7212f8d2a6e84ad2a4a7f4a0ade");
    TestCnHash(2, "a4a87ce72d401be0827cf6da50bcea66e7f9fab8a28969bf05240fa3190b418d76e3b024f2ee40194fb32a14e341de99821b60ea402c557d7b92d964976c6437",
                  "00000000000000000000000000000000000000000000000000000000000000007ca02b19a3e15df3c1edd180e6dd108c5f41876d2344133396aa9d05702e0c8f");
    TestCnHash(2, "ba3b66fc6b4f5caa7a7d312a0467ef3f068ffc2a309133cc8ebfe6545bee72fc8d2153268da88628dad04e4e3b0a738dc58f87b0c8044ee212b2313a59a538d1",
                  "00000000000000000000000000000000000000000000000000000000000000002a0fd0a52279953071774fd7b51a104fdec6fa23f8a6910495aa15786dca4bdc");
    TestCnHash(2, "bee2490e5877ecf3ec3dc54d88f48151539b56edb4ea6f1d3227614dbfcf3759b83d0e1d724b14e683243f50404ba31bdab86ead2ebc9ace766efa214fa934ff",
                  "0000000000000000000000000000000000000000000000000000000000000000a33918622063c26f513b138456611fe45b6e2aae38b1711122ee562480ee2e58");
    TestCnHash(2, "c9aeceb793cab3fa7ef55f07b1399975977e4b734df6f43d705d60523d73b5c650a4783bde9915dd55b3b03923a8fd1c12ef6ffb8530c0c8b20d2c2fc27f9276",
                  "000000000000000000000000000000000000000000000000000000000000000003707c430558581e6e87c0202899747a0ad894c602a63cbf93d593615308625d");
    TestCnHash(2, "d1fa8d9de747b2ba761fcdbccd68ca66f94cc844f73a09a26ef95c393a7ba7e2c086ce012d9ae2e7e33553306279e754ad457f2402a12736c28f9ea2c28d7223",
                  "00000000000000000000000000000000000000000000000000000000000000001c608ad38deec40dfb27d5247ea0ac048b8a6509e137c2056303c4a8d8e0cabf");
}

BOOST_AUTO_TEST_CASE(cryptonight_cnlite_hash) {
    TestCnHash(3, "0e8b10782208af28c501265320395f3b9d3e56d1863055e3b6d465ed57a3a2eb7a42bf41358b50d4615d6fb9e06417e44f7f0455c85b4039f3cbcd175bd462e8",
                  "00000000000000000000000000000000000000000000000000000000000000000019362c35041c8dc1f82a1df6969f10af711b89fccddd01475ea244ad75d260");
    TestCnHash(3, "315bd2ec1c5df021cf375cd3b8236158a7d2d653b28e62d7cbf5a591682a237be01670257c9fa39fd959d027d11c6e1ee02af7cff8350f53c827c2731c46fee5",
                  "0000000000000000000000000000000000000000000000000000000000000000a8546bca87fded9ce540e2a31bb9f5080b288f13bf686b5299a4c5ddd7fba98b");
    TestCnHash(3, "4958c949771167786692167f6718e050e4739d49ce5d6a8556e139f0cde363d32875306201abdb51de62acbb6fbde62b9c068cb67b5fcd3a9bac6dd00d7ffd42",
                  "0000000000000000000000000000000000000000000000000000000000000000da8dfe4964d2046dd42e95eb45c4290d3f02cb038643f926758bd0ad73aa849e");
    TestCnHash(3, "60715ce478470261a68dbfc7344845d0d91bc6239ac25550f3832ffee45a5c876f334b5cf16995c7d09ff9cbc350c1c08f000c9beb1d274caa2a9c61840aa1de",
                  "00000000000000000000000000000000000000000000000000000000000000005f9266164b2b84afbb617dfcfeeb499353ff60f17ef553a7a961ac42619a2a3b");
    TestCnHash(3, "9187bc9aa3fa352c069fef00550c80ecf1586d5b27b599aa9a81fbb3b5914293c0d47f54397fc41113fdcad33af720606c2421fae428a4450d4996710561724c",
                  "0000000000000000000000000000000000000000000000000000000000000000f0d55e7d83989768e6c7987610789af1cd3c475ae9a375f0e1a2f1182be25774");
    TestCnHash(3, "970c4f67c11d7e3a29935e74d7865d20fcb6016e64991444740fb66cfa09ac8415cb08c7013db9e04cb2216d7f02cb5daa875d9bebced38559696b9f1333f4a0",
                  "00000000000000000000000000000000000000000000000000000000000000000005f5fb38930ec6ac8490f1a723fe4824f4cabd31495198f296be16040c13c1");
    TestCnHash(3, "d1536e49f4df45cbf97d34c5893ee21674ca1f7dc2c966926851fb0b6d036d595e0cce2e4775f6726647e56dc744738d998c6c39a8d57e238b84fe7f130eaacd",
                  "0000000000000000000000000000000000000000000000000000000000000000c9760b387c234b5d2673da8ae2182c87db04a7ce1bc263adcfc60f2c7c0dc13a");
    TestCnHash(3, "e6d2621a5741a7a7e2098d99a9713e7f0a985ce8b6e92230ba6b7908e7eab70b50a28395811192cbc5aa02cf4bf72c285725dc8faec54dd37313445faf261170",
                  "0000000000000000000000000000000000000000000000000000000000000000fede2ac1f5904ed45a979238481af0c6505c84f4c46628c754cdcee650045513");
}

BOOST_AUTO_TEST_CASE(cryptonight_turtle_hash) {
    TestCnHash(4, "054da70aa74e3bf1cc2725e54773f3d2ae83f5c2ec90ab87682855b70fbd6dc4f9d9975fe2997de3493baf7086dda6421060cb1ecb84921194f83615223ed013",
                  "0000000000000000000000000000000000000000000000000000000000000000ac9c4e80b4759b3db603b132edbe3dc3b443070862c38a3a784ec66f872d74f4");
    TestCnHash(4, "31c5b121ffe0f0e8ef136bb987ef756ee824e1862fdb74856912b1b5902acb8501c9d3ade175d7042507a11d6b9e1bdc2d6f8dca6dcb54dfe6a24e5a2751438b",
                  "0000000000000000000000000000000000000000000000000000000000000000c8804fad6417c278fce9e444d307c7ac4c4e9280ea7c2a9565872022d93679a1");
    TestCnHash(4, "397769628a2ea9e4e250690933bc9c8b943845ed8186f48b8b882ba547f58e223e715972f57985d52c6f707624b4b59b88dcf75e806f047ccc742cef02a75dba",
                  "000000000000000000000000000000000000000000000000000000000000000000108af0879bf342f2d021635f1434b080e2fd36264a8df9abfcca484c62ed81");
    TestCnHash(4, "7897ce03a62511eaf108e75a533ba8478fd17b8319c8211f8ed499421f498455b8ac3fa7e19099189640c3cf56298268d9900faff1e4052e75934d2770af7291",
                  "0000000000000000000000000000000000000000000000000000000000000000001b70b3d4c0e9d2cb3bc3a612b424212f90f4f91c7d4865a98945bcf13d5395");
    TestCnHash(4, "876d2790dd1ee144e83cabcb0c72e60ba8d32f9ba6d811c44b6f3a0a93046f18f14d7f4730bb56ef68a89575695cf718f59a6957d1427bf7c74bb3cc56d09be8",
                  "0000000000000000000000000000000000000000000000000000000000000000000bb2019335662536fd3f1b14a4563c8cbdb418c93ef0416db5f9af19eb6e19");
    TestCnHash(4, "9ce70975879801658efc65de651ee158a41e038dee82d4eb88b53414d84b7c630e050b765d10e82dd81acc6d14757ea153bd73c50eb6c0c3407ab8a0b2aa64eb",
                  "00000000000000000000000000000000000000000000000000000000000000002ba169136b5385a90a46ed66e76c4f78f378eaa2fb47a28bc2233187fd206ee4");
    TestCnHash(4, "da6b70cfc0573d1332a9d34838cd768a5d400ec1ede93747319a33f4ebb142c9aa546382239e70adbe876ce6ad30c9e6332145639040d8863507cc4181123ccd",
                  "00000000000000000000000000000000000000000000000000000000000000000123f428c9d358c03eddb0d33a29af35692e196373fbb82ded1ca22ffa37e210");
}

BOOST_AUTO_TEST_CASE(cryptonight_turtlelite_hash) {
    TestCnHash(5, "14cf018fac801ec378be632d4207da5475a53a680af5550f7a1216e3c7bb0e44b1f78b6a3f6d32bc3cc468e8fd9f8b96e5c505c3e3331cdf43509135552c9150",
                  "00000000000000000000000000000000000000000000000000000000000000002a289054e9ed32826c9773d330a63eaa9a33c9de6e80f24ec6f8cdeefe8b726f");
    TestCnHash(5, "35856979caa2fb7d0407b7cbf13cda7c7827727c97365de23a4b43df6f38c6f6c09899092161b4752564ca5dc45f015556bfcf1e9a0de4f9433990c5a9fb2f0e",
                  "0000000000000000000000000000000000000000000000000000000000000000534bdd6f1407435ccc4c96ec8aa712d507766b70f4fff04880ba807c7b84895d");
    TestCnHash(5, "67c90dc094ebbc29ed0f6639c02233f632b98388479eed88c060c73fdf77b6942062d2854bfb3f0399bd27a0dadc3ac9534782e2102ab09c3100f73fa9e61948",
                  "0000000000000000000000000000000000000000000000000000000000000000f06516325851f4d7e66979d7309c3b0fafb9a56cb5f3a808c031e5413b76fb15");
    TestCnHash(5, "bf05c0b0fcbbbfe97e1a7c34fd75eda742c652f1670f06c90041b3909677d259c7d572ca2b0e3f3e3439c6910d66e1232883172081ac0856d38545d3bcedc2ad",
                  "00000000000000000000000000000000000000000000000000000000000000002aec77c88476c1043850fba3e4f1dcb116d4f0208fbfb6239f917b8f2a7e493f");
    TestCnHash(5, "e249f20d570eb92d989c36eab1409b2a98479413624c524f6fca7721ef04ec70fce26991f0b5872203de6bcae1ef2b723e0aa1c26f9c7a1bfe696c22f5d84814",
                  "00000000000000000000000000000000000000000000000000000000000000002796a3dac94528970f4d86d90558c128adcd67409514b499ac16bf28cbc567a1");
}

BOOST_AUTO_TEST_SUITE_END()
