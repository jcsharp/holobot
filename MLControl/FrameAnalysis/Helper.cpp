///-----------------------------------------------------------------
///   Class:          Helper
///   Description:    Helper String Operations and Mapping functions
///   Author:         Jhalak Patel
///   Revision History:
///-----------------------------------------------------------------

#include "Helper.h"
#include "Globals.h"

UYVY_MACRO_PIXEL YUY2InputFrame[inputImageHeight][inputImageWidth / 2];
UYVY_MACRO_PIXEL YUY2OutputFrame[outputImageHeight][outputImageWidth];
BYTE resizedImagedataArray[featureImageWidth * featureImageHeight * imageChannels];
BYTE originalImagedataArray[inputImageHeight * inputImageWidth * imageChannels];
BYTE newOriginalImagedataArray[inputImageHeight * inputImageWidth * (imageChannels + 1)];
RGBTRIPLELOCAL RGBInputFrame[inputImageHeight][inputImageWidth];
RGBTRIPLELOCAL rgbBmpFrame[outputImageHeight][outputImageWidth];
YUVTRIPLE pYuv[outputImageHeight][outputImageWidth];
std::vector<float> features;
bool imageInjected = false;
bool modelGenStatus = false;
int imageClassificationCounter = 0;
std::atomic_bool evaluating;

Platform::String^ Helper::stringToPlatformString(std::string inputString) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(inputString);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());
	return retVal;
}

std::string Helper::PlatformStringToString(Platform::String^ inputString) {
	std::wstring textToConvert = std::wstring(inputString->Data());
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string converted_str = converter.to_bytes(textToConvert);
	return converted_str;
}


std::string Helper::MapImageClassNumberToImageClassString(int ImageClass)
{
	switch (ImageClass)
	{
	case 610:
	case 608:
	case 617:
	case 652:
	case 655:
	case 697:
	case 834:
	case 836:
	case 841:
	case 850:
	case 983:
	case 456:
	case 457:
	case 515:
	case 578:
	case 568:
	case 869:
	case 399:
	case 400:
	case 501:
	case 837:
	case 601:
	case 903:
	case 264:
	case 451:
	case 906:
	case 785:
	case 465:
	case 474:
	case 552:
	case 614:
	case 689:
	case 735:
	case 824:
	case 887:
	case 982:
	case 998:
	case 796:
	case 643: return "person"; break;
	case 0: return "tench"; break;
	case 1: return "goldfish"; break;
	case 2: return "great white shark"; break;
	case 3: return "tiger shark"; break;
	case 4: return "hammerhead"; break;
	case 5: return "electric ray"; break;
	case 6: return "stingray"; break;
	case 7: return "cock"; break;
	case 8: return "hen"; break;
	case 9: return "ostrich"; break;
	case 10: return "brambling"; break;
	case 11: return "goldfinch"; break;
	case 12: return "house finch"; break;
	case 13: return "junco"; break;
	case 14: return "indigo bunting"; break;
	case 15: return "robin"; break;
	case 16: return "bulbul"; break;
	case 17: return "jay"; break;
	case 19: return "chickadee"; break;
	case 18: return "magpie"; break;
	case 20: return "water ouzel"; break;
	case 21: return "kite"; break;
	case 22: return "bald eagle"; break;
	case 23: return "vulture"; break;
	case 24: return "great grey owl"; break;
	case 25: return "European fire salamander"; break;
	case 26: return "common newt"; break;
	case 27: return "eft"; break;
	case 28: return "spotted salamander"; break;
	case 29: return "axolotl"; break;
	case 30: return "bullfrog"; break;
	case 31: return "tree frog"; break;
	case 32: return "tailed frog"; break;
	case 33: return "loggerhead"; break;
	case 34: return "leatherback turtle"; break;
	case 35: return "mud turtle"; break;
	case 36: return "terrapin"; break;
	case 37: return "box turtle"; break;
	case 38: return "banded gecko"; break;
	case 39: return "common iguana"; break;
	case 40: return "American chameleon"; break;
	case 41: return "whiptail"; break;
	case 42: return "agama"; break;
	case 43: return "frilled lizard"; break;
	case 44: return "alligator lizard"; break;
	case 45: return "Gila monster"; break;
	case 46: return "green lizard"; break;
	case 47: return "African chameleon"; break;
	case 48: return "Komodo dragon"; break;
	case 49: return "African crocodile"; break;
	case 50: return "American alligator"; break;
	case 51: return "triceratops"; break;
	case 52: return "thunder snake"; break;
	case 53: return "ringneck snake"; break;
	case 54: return "hognose snake"; break;
	case 55: return "green snake"; break;
	case 56: return "king snake"; break;
	case 57: return "garter snake"; break;
	case 58: return "water snake"; break;
	case 59: return "vine snake"; break;
	case 60: return "night snake"; break;
	case 61: return "boa constrictor"; break;
	case 62: return "rock python"; break;
	case 63: return "Indian cobra"; break;
	case 64: return "green mamba"; break;
	case 65: return "sea snake"; break;
	case 66: return "horned viper"; break;
	case 67: return "diamondback"; break;
	case 68: return "sidewinder"; break;
	case 69: return "trilobite"; break;
	case 70: return "harvestman"; break;
	case 71: return "scorpion"; break;
	case 72: return "black and gold garden spider"; break;
	case 73: return "barn spider"; break;
	case 74: return "garden spider"; break;
	case 75: return "black widow"; break;
	case 76: return "tarantula"; break;
	case 77: return "wolf spider"; break;
	case 78: return "tick"; break;
	case 79: return "centipede"; break;
	case 80: return "black grouse"; break;
	case 81: return "ptarmigan"; break;
	case 82: return "ruffed grouse"; break;
	case 83: return "prairie chicken"; break;
	case 84: return "peacock"; break;
	case 85: return "quail"; break;
	case 86: return "partridge"; break;
	case 87: return "African grey"; break;
	case 88: return "macaw"; break;
	case 89: return "sulphur-crested cockatoo"; break;
	case 90: return "lorikeet"; break;
	case 91: return "coucal"; break;
	case 92: return "bee eater"; break;
	case 93: return "hornbill"; break;
	case 94: return "hummingbird"; break;
	case 95: return "jacamar"; break;
	case 96: return "toucan"; break;
	case 97: return "drake"; break;
	case 98: return "red-breasted merganser"; break;
	case 99: return "goose"; break;
	case 100: return "black swan"; break;
	case 101: return "tusker"; break;
	case 102: return "echidna"; break;
	case 103: return "platypus"; break;
	case 104: return "wallaby"; break;
	case 105: return "koala"; break;
	case 106: return "wombat"; break;
	case 107: return "jellyfish"; break;
	case 108: return "sea anemone"; break;
	case 109: return "brain coral"; break;
	case 110: return "flatworm"; break;
	case 111: return "nematode"; break;
	case 112: return "conch"; break;
	case 113: return "snail"; break;
	case 114: return "slug"; break;
	case 115: return "sea slug"; break;
	case 116: return "chiton"; break;
	case 117: return "chambered nautilus"; break;
	case 118: return "Dungeness crab"; break;
	case 119: return "rock crab"; break;
	case 120: return "fiddler crab"; break;
	case 121: return "king crab"; break;
	case 122: return "American lobster"; break;
	case 123: return "spiny lobster"; break;
	case 124: return "crayfish"; break;
	case 125: return "hermit crab"; break;
	case 126: return "isopod"; break;
	case 127: return "white stork"; break;
	case 128: return "black stork"; break;
	case 129: return "spoonbill"; break;
	case 130: return "flamingo"; break;
	case 131: return "little blue heron"; break;
	case 132: return "American egret"; break;
	case 133: return "bittern"; break;
	case 134: return "crane"; break;
	case 135: return "limpkin"; break;
	case 136: return "European gallinule"; break;
	case 137: return "American coot"; break;
	case 138: return "bustard"; break;
	case 139: return "ruddy turnstone"; break;
	case 140: return "red-backed sandpiper"; break;
	case 141: return "redshank"; break;
	case 142: return "dowitcher"; break;
	case 143: return "oystercatcher"; break;
	case 144: return "pelican"; break;
	case 145: return "king penguin"; break;
	case 146: return "albatross"; break;
	case 147: return "grey whale"; break;
	case 148: return "killer whale"; break;
	case 149: return "dugong"; break;
	case 150: return "sea lion"; break;
	case 151: return "Chihuahua"; break;
	case 152: return "Japanese spaniel"; break;
	case 153: return "Maltese dog"; break;
	case 154: return "Pekinese"; break;
	case 155: return "Shih-Tzu"; break;
	case 156: return "Blenheim spaniel"; break;
	case 157: return "papillon"; break;
	case 158: return "toy terrier"; break;
	case 159: return "Rhodesian ridgeback"; break;
	case 160: return "Afghan hound"; break;
	case 161: return "basset"; break;
	case 162: return "beagle"; break;
	case 163: return "bloodhound"; break;
	case 164: return "bluetick"; break;
	case 165: return "black-and-tan coonhound"; break;
	case 166: return "Walker hound"; break;
	case 167: return "English foxhound"; break;
	case 168: return "redbone"; break;
	case 169: return "borzoi"; break;
	case 170: return "Irish wolfhound"; break;
	case 171: return "Italian greyhound"; break;
	case 172: return "whippet"; break;
	case 173: return "Ibizan hound"; break;
	case 174: return "Norwegian elkhound"; break;
	case 175: return "otterhound"; break;
	case 176: return "Saluki"; break;
	case 177: return "Scottish deerhound"; break;
	case 178: return "Weimaraner"; break;
	case 179: return "Staffordshire bullterrier"; break;
	case 180: return "American Staffordshire terrier"; break;
	case 181: return "Bedlington terrier"; break;
	case 182: return "Border terrier"; break;
	case 183: return "Kerry blue terrier"; break;
	case 184: return "Irish terrier"; break;
	case 185: return "Norfolk terrier"; break;
	case 186: return "Norwich terrier"; break;
	case 187: return "Yorkshire terrier"; break;
	case 188: return "wire-haired fox terrier"; break;
	case 189: return "Lakeland terrier"; break;
	case 190: return "Sealyham terrier"; break;
	case 191: return "Airedale"; break;
	case 192: return "cairn"; break;
	case 193: return "Australian terrier"; break;
	case 194: return "Dandie Dinmont"; break;
	case 195: return "Boston bull"; break;
	case 196: return "miniature schnauzer"; break;
	case 197: return "giant schnauzer"; break;
	case 198: return "standard schnauzer"; break;
	case 199: return "Scotch terrier"; break;
	case 200: return "Tibetan terrier"; break;
	case 201: return "silky terrier"; break;
	case 202: return "soft-coated wheaten terrier"; break;
	case 203: return "West Highland white terrier"; break;
	case 204: return "Lhasa"; break;
	case 205: return "flat-coated retriever"; break;
	case 206: return "curly-coated retriever"; break;
	case 207: return "golden retriever"; break;
	case 208: return "Labrador retriever"; break;
	case 209: return "Chesapeake Bay retriever"; break;
	case 210: return "German short-haired pointer"; break;
	case 211: return "vizsla"; break;
	case 212: return "English setter"; break;
	case 213: return "Irish setter"; break;
	case 214: return "Gordon setter"; break;
	case 215: return "Brittany spaniel"; break;
	case 216: return "clumber"; break;
	case 217: return "English springer"; break;
	case 218: return "Welsh springer spaniel"; break;
	case 219: return "cocker spaniel"; break;
	case 220: return "Sussex spaniel"; break;
	case 221: return "Irish water spaniel"; break;
	case 222: return "kuvasz"; break;
	case 223: return "schipperke"; break;
	case 224: return "groenendael"; break;
	case 225: return "malinois"; break;
	case 226: return "briard"; break;
	case 227: return "kelpie"; break;
	case 228: return "komondor"; break;
	case 229: return "Old English sheepdog"; break;
	case 230: return "Shetland sheepdog"; break;
	case 231: return "collie"; break;
	case 232: return "Border collie"; break;
	case 233: return "Bouvier des Flandres"; break;
	case 234: return "Rottweiler"; break;
	case 235: return "German shepherd"; break;
	case 236: return "Doberman"; break;
	case 237: return "miniature pinscher"; break;
	case 238: return "Greater Swiss Mountain dog"; break;
	case 239: return "Bernese mountain dog"; break;
	case 240: return "Appenzeller"; break;
	case 241: return "EntleBucher"; break;
	case 242: return "boxer"; break;
	case 243: return "bull mastiff"; break;
	case 244: return "Tibetan mastiff"; break;
	case 245: return "French bulldog"; break;
	case 246: return "Great Dane"; break;
	case 247: return "Saint Bernard"; break;
	case 248: return "Eskimo dog"; break;
	case 249: return "malamute"; break;
	case 250: return "Siberian husky"; break;
	case 251: return "dalmatian"; break;
	case 252: return "affenpinscher"; break;
	case 253: return "basenji"; break;
	case 254: return "pug"; break;
	case 255: return "Leonberg"; break;
	case 256: return "Newfoundland"; break;
	case 257: return "Great Pyrenees"; break;
	case 258: return "Samoyed"; break;
	case 259: return "Pomeranian"; break;
	case 260: return "chow"; break;
	case 261: return "keeshond"; break;
	case 262: return "Brabancon griffon"; break;
	case 263: return "Pembroke"; break;
	//case 264: return "Cardigan"; break;
	case 265: return "toy poodle"; break;
	case 266: return "miniature poodle"; break;
	case 267: return "standard poodle"; break;
	case 268: return "Mexican hairless"; break;
	case 269: return "timber wolf"; break;
	case 270: return "white wolf"; break;
	case 271: return "red wolf"; break;
	case 272: return "coyote"; break;
	case 273: return "dingo"; break;
	case 274: return "dhole"; break;
	case 275: return "African hunting dog"; break;
	case 276: return "hyena"; break;
	case 277: return "red fox"; break;
	case 278: return "kit fox"; break;
	case 279: return "Arctic fox"; break;
	case 280: return "grey fox"; break;
	case 281: return "tabby"; break;
	case 282: return "tiger cat"; break;
	case 283: return "Persian cat"; break;
	case 284: return "Siamese cat"; break;
	case 285: return "Egyptian cat"; break;
	case 286: return "cougar"; break;
	case 287: return "lynx"; break;
	case 288: return "leopard"; break;
	case 289: return "snow leopard"; break;
	case 290: return "jaguar"; break;
	case 291: return "lion"; break;
	case 292: return "tiger"; break;
	case 293: return "cheetah"; break;
	case 294: return "brown bear"; break;
	case 295: return "American black bear"; break;
	case 296: return "ice bear"; break;
	case 297: return "sloth bear"; break;
	case 298: return "mongoose"; break;
	case 299: return "meerkat"; break;
	case 300: return "tiger beetle"; break;
	case 301: return "ladybug"; break;
	case 302: return "ground beetle"; break;
	case 303: return "long-horned beetle"; break;
	case 304: return "leaf beetle"; break;
	case 305: return "dung beetle"; break;
	case 306: return "rhinoceros beetle"; break;
	case 307: return "weevil"; break;
	case 308: return "fly"; break;
	case 309: return "bee"; break;
	case 310: return "ant"; break;
	case 311: return "grasshopper"; break;
	case 312: return "cricket"; break;
	case 313: return "walking stick"; break;
	case 314: return "cockroach"; break;
	case 315: return "mantis"; break;
	case 316: return "cicada"; break;
	case 317: return "leafhopper"; break;
	case 318: return "lacewing"; break;
	case 319: return "dragonfly"; break;
	case 320: return "damselfly"; break;
	case 321: return "admiral"; break;
	case 322: return "ringlet"; break;
	case 323: return "monarch"; break;
	case 324: return "cabbage butterfly"; break;
	case 325: return "sulphur butterfly"; break;
	case 326: return "lycaenid"; break;
	case 327: return "starfish"; break;
	case 328: return "sea urchin"; break;
	case 329: return "sea cucumber"; break;
	case 330: return "wood rabbit"; break;
	case 331: return "hare"; break;
	case 332: return "Angora"; break;
	case 333: return "hamster"; break;
	case 334: return "porcupine"; break;
	case 335: return "fox squirrel"; break;
	case 336: return "marmot"; break;
	case 337: return "beaver"; break;
	case 338: return "guinea pig"; break;
	case 339: return "sorrel"; break;
	case 340: return "zebra"; break;
	case 341: return "hog"; break;
	case 342: return "wild boar"; break;
	case 343: return "warthog"; break;
	case 344: return "hippopotamus"; break;
	case 345: return "ox"; break;
	case 346: return "water buffalo"; break;
	case 347: return "bison"; break;
	case 348: return "ram"; break;
	case 349: return "bighorn"; break;
	case 350: return "ibex"; break;
	case 351: return "hartebeest"; break;
	case 352: return "impala"; break;
	case 353: return "gazelle"; break;
	case 354: return "Arabian camel"; break;
	case 355: return "llama"; break;
	case 356: return "weasel"; break;
	case 357: return "mink"; break;
	case 358: return "polecat"; break;
	case 359: return "black-footed ferret"; break;
	case 360: return "otter"; break;
	case 361: return "skunk"; break;
	case 362: return "badger"; break;
	case 363: return "armadillo"; break;
	case 364: return "three-toed sloth"; break;
	case 365: return "orangutan"; break;
	case 366: return "gorilla"; break;
	case 367: return "chimpanzee"; break;
	case 368: return "gibbon"; break;
	case 369: return "siamang"; break;
	case 370: return "guenon"; break;
	case 371: return "patas"; break;
	case 372: return "baboon"; break;
	case 373: return "macaque"; break;
	case 374: return "langur"; break;
	case 375: return "colobus"; break;
	case 376: return "proboscis monkey"; break;
	case 377: return "marmoset"; break;
	case 378: return "capuchin"; break;
	case 379: return "howler monkey"; break;
	case 380: return "titi"; break;
	case 381: return "spider monkey"; break;
	case 382: return "squirrel monkey"; break;
	case 383: return "Madagascar cat"; break;
	case 384: return "indri"; break;
	case 385: return "Indian elephant"; break;
	case 386: return "African elephant"; break;
	case 387: return "lesser panda"; break;
	case 388: return "giant panda"; break;
	case 389: return "barracouta"; break;
	case 390: return "eel"; break;
	case 391: return "coho"; break;
	case 392: return "rock beauty"; break;
	case 393: return "anemone fish"; break;
	case 394: return "sturgeon"; break;
	case 395: return "gar"; break;
	case 396: return "lionfish"; break;
	case 397: return "puffer"; break;
	case 398: return "abacus"; break;
	//case 399: return "abaya"; break;
	//case 400: return "academic gown"; break;
	case 401: return "accordion"; break;
	case 402: return "acoustic guitar"; break;
	case 403: return "aircraft carrier"; break;
	case 404: return "airliner"; break;
	case 405: return "airship"; break;
	case 406: return "altar"; break;
	case 407: return "ambulance"; break;
	case 408: return "amphibian"; break;
	case 409: return "analog clock"; break;
	case 410: return "apiary"; break;
	case 411: return "apron"; break;
	case 412: return "ashcan"; break;
	case 413: return "assault rifle"; break;
	case 414: return "backpack"; break;
	case 415: return "bakery"; break;
	case 416: return "balance beam"; break;
	case 417: return "balloon"; break;
	case 418: return "ballpoint"; break;
	case 419: return "Band Aid"; break;
	case 420: return "banjo"; break;
	case 421: return "bannister"; break;
	case 422: return "barbell"; break;
	case 423: return "barber chair"; break;
	case 424: return "barbershop"; break;
	case 425: return "barn"; break;
	case 426: return "barometer"; break;
	case 427: return "barrel"; break;
	case 428: return "barrow"; break;
	case 429: return "baseball"; break;
	case 430: return "basketball"; break;
	case 431: return "bassinet"; break;
	case 432: return "bassoon"; break;
	case 433: return "bathing cap"; break;
	case 434: return "bath towel"; break;
	case 435: return "bathtub"; break;
	case 436: return "beach wagon"; break;
	case 437: return "beacon"; break;
	case 438: return "beaker"; break;
	case 439: return "bearskin"; break;
	case 440: return "beer bottle"; break;
	case 441: return "beer glass"; break;
	case 442: return "bell cote"; break;
	case 443: return "bib"; break;
	case 444: return "bicycle-built-for-two"; break;
	case 445: return "bikini"; break;
	case 446: return "binder"; break;
	case 447: return "binoculars"; break;
	case 448: return "birdhouse"; break;
	case 449: return "boathouse"; break;
	case 450: return "bobsled"; break;
	//case 451: return "bolo tie"; break;
	case 452: return "bonnet"; break;
	case 453: return "bookcase"; break;
	case 454: return "bookshop"; break;
	case 455: return "bottlecap"; break;
	//case 456: return "bow"; break;
	//case 457: return "bow tie"; break;
	case 458: return "brass"; break;
	case 459: return "brassiere"; break;
	case 460: return "breakwater"; break;
	case 461: return "breastplate"; break;
	case 462: return "broom"; break;
	case 463: return "bucket"; break;
	case 464: return "buckle"; break;
	//case 465: return "bulletproof vest"; break;
	case 466: return "bullet train"; break;
	case 467: return "butcher shop"; break;
	case 468: return "cab"; break;
	case 469: return "caldron"; break;
	case 470: return "candle"; break;
	case 471: return "cannon"; break;
	case 472: return "canoe"; break;
	case 473: return "can opener"; break;
	//case 474: return "cardigan"; break;
	case 475: return "car mirror"; break;
	case 476: return "carousel"; break;
	case 477: return "carpenter's kit"; break;
	case 478: return "carton"; break;
	case 479: return "car wheel"; break;
	case 480: return "cash machine"; break;
	case 481: return "cassette"; break;
	case 482: return "cassette player"; break;
	case 483: return "castle"; break;
	case 484: return "catamaran"; break;
	case 485: return "CD player"; break;
	case 486: return "cello"; break;
	case 487: return "cellular telephone"; break;
	case 488: return "chain"; break;
	case 489: return "chainlink fence"; break;
	case 490: return "chain mail"; break;
	case 491: return "chain saw"; break;
	case 492: return "chest"; break;
	case 493: return "chiffonier"; break;
	case 494: return "chime"; break;
	case 495: return "china cabinet"; break;
	case 496: return "Christmas stocking"; break;
	case 497: return "church"; break;
	case 498: return "cinema"; break;
	case 499: return "cleaver"; break;
	case 500: return "cliff dwelling"; break;
	//case 501: return "cloak"; break;
	case 502: return "clog"; break;
	case 503: return "cocktail shaker"; break;
	case 504: return "coffee mug"; break;
	case 505: return "coffeepot"; break;
	case 506: return "coil"; break;
	case 507: return "combination lock"; break;
	case 508: return "computer keyboard"; break;
	case 509: return "confectionery"; break;
	case 510: return "container ship"; break;
	case 511: return "convertible"; break;
	case 512: return "corkscrew"; break;
	case 513: return "cornet"; break;
	case 514: return "cowboy boot"; break;
	//case 515: return "cowboy hat"; break;
	case 516: return "cradle"; break;
	case 517: return "crane"; break;
	case 518: return "crash helmet"; break;
	case 519: return "crate"; break;
	case 520: return "crib"; break;
	case 521: return "Crock Pot"; break;
	case 522: return "croquet ball"; break;
	case 523: return "crutch"; break;
	case 524: return "cuirass"; break;
	case 525: return "dam"; break;
	case 526: return "desk"; break;
	case 527: return "desktop computer"; break;
	case 528: return "dial telephone"; break;
	case 529: return "diaper"; break;
	case 530: return "digital clock"; break;
	case 531: return "digital watch"; break;
	case 532: return "dining table"; break;
	case 533: return "dishrag"; break;
	case 534: return "dishwasher"; break;
	case 535: return "disk brake"; break;
	case 536: return "dock"; break;
	case 537: return "dogsled"; break;
	case 538: return "dome"; break;
	case 539: return "doormat"; break;
	case 540: return "drilling platform"; break;
	case 541: return "drum"; break;
	case 542: return "drumstick"; break;
	case 543: return "dumbbell"; break;
	case 544: return "Dutch oven"; break;
	case 545: return "electric fan"; break;
	case 546: return "electric guitar"; break;
	case 547: return "electric locomotive"; break;
	case 548: return "entertainment center"; break;
	case 549: return "envelope"; break;
	case 550: return "espresso maker"; break;
	case 551: return "face powder"; break;
	//case 552: return "feather boa"; break;
	case 553: return "file"; break;
	case 554: return "fireboat"; break;
	case 555: return "fire engine"; break;
	case 556: return "fire screen"; break;
	case 557: return "flagpole"; break;
	case 558: return "flute"; break;
	case 559: return "folding chair"; break;
	case 560: return "football helmet"; break;
	case 561: return "forklift"; break;
	case 562: return "fountain"; break;
	case 563: return "fountain pen"; break;
	case 564: return "four-poster"; break;
	case 565: return "freight car"; break;
	case 566: return "French horn"; break;
	case 567: return "frying pan"; break;
	//case 568: return "fur coat"; break;
	case 569: return "garbage truck"; break;
	case 570: return "gasmask"; break;
	case 571: return "gas pump"; break;
	case 572: return "goblet"; break;
	case 573: return "go-kart"; break;
	case 574: return "golf ball"; break;
	case 575: return "golfcart"; break;
	case 576: return "gondola"; break;
	case 577: return "gong"; break;
	//case 578: return "gown"; break;
	case 579: return "grand piano"; break;
	case 580: return "greenhouse"; break;
	case 581: return "grille"; break;
	case 582: return "grocery store"; break;
	case 583: return "guillotine"; break;
	case 584: return "hair slide"; break;
	case 585: return "hair spray"; break;
	case 586: return "half track"; break;
	case 587: return "hammer"; break;
	case 588: return "hamper"; break;
	case 589: return "hand blower"; break;
	case 590: return "hand-held computer"; break;
	case 591: return "handkerchief"; break;
	case 592: return "hard disc"; break;
	case 593: return "harmonica"; break;
	case 594: return "harp"; break;
	case 595: return "harvester"; break;
	case 596: return "hatchet"; break;
	case 597: return "holster"; break;
	case 598: return "home theater"; break;
	case 599: return "honeycomb"; break;
	case 600: return "hook"; break;
	//case 601: return "hoopskirt"; break;
	case 602: return "horizontal bar"; break;
	case 603: return "horse cart"; break;
	case 604: return "hourglass"; break;
	case 605: return "iPod"; break;
	case 606: return "iron"; break;
	case 607: return "jack - o'-lantern"; break;
	//case 608: return "jean"; break;
	case 609: return "jeep"; break;
	//case 610: return "jersey"; break;
	case 611: return "jigsaw puzzle"; break;
	case 612: return "jinrikisha"; break;
	case 613: return "joystick"; break;
	//case 614: return "kimono"; break;
	case 615: return "knee pad"; break;
	case 616: return "knot"; break;
	//case 617: return "lab coat"; break;
	case 618: return "ladle"; break;
	case 619: return "lampshade"; break;
	case 620: return "laptop"; break;
	case 621: return "lawn mower"; break;
	case 622: return "lens cap"; break;
	case 623: return "letter opener"; break;
	case 624: return "library"; break;
	case 625: return "lifeboat"; break;
	case 626: return "lighter"; break;
	case 627: return "limousine"; break;
	case 628: return "liner"; break;
	case 629: return "lipstick"; break;
	case 630: return "Loafer"; break;
	case 631: return "lotion"; break;
	case 632: return "loudspeaker"; break;
	case 633: return "loupe"; break;
	case 634: return "lumbermill"; break;
	case 635: return "magnetic compass"; break;
	case 636: return "mailbag"; break;
	case 637: return "mailbox"; break;
	case 638: return "maillot"; break;
	case 639: return "maillot"; break;
	case 640: return "manhole cover"; break;
	case 641: return "maraca"; break;
	case 642: return "marimba"; break;
	//case 643: return "mask"; break;
	case 644: return "matchstick"; break;
	case 645: return "maypole"; break;
	case 646: return "maze"; break;
	case 647: return "measuring cup"; break;
	case 648: return "medicine chest"; break;
	case 649: return "megalith"; break;
	case 650: return "microphone"; break;
	case 651: return "microwave"; break;
	//case 652: return "military uniform"; break;
	case 653: return "milk can"; break;
	case 654: return "minibus"; break;
	//case 655: return "miniskirt"; break;
	case 656: return "minivan"; break;
	case 657: return "missile"; break;
	case 658: return "mitten"; break;
	case 659: return "mixing bowl"; break;
	case 660: return "mobile home"; break;
	case 661: return "Model T"; break;
	case 662: return "modem"; break;
	case 663: return "monastery"; break;
	case 664: return "monitor"; break;
	case 665: return "moped"; break;
	case 666: return "mortar"; break;
	case 667: return "mortarboard"; break;
	case 668: return "mosque"; break;
	case 669: return "mosquito net"; break;
	case 670: return "motor scooter"; break;
	case 671: return "mountain bike"; break;
	case 672: return "mountain tent"; break;
	case 673: return "mouse"; break;
	case 674: return "mousetrap"; break;
	case 675: return "moving van"; break;
	case 676: return "muzzle"; break;
	case 677: return "nail"; break;
	case 678: return "neck brace"; break;
	case 679: return "necklace"; break;
	case 680: return "nipple"; break;
	case 681: return "notebook"; break;
	case 682: return "obelisk"; break;
	case 683: return "oboe"; break;
	case 684: return "ocarina"; break;
	case 685: return "odometer"; break;
	case 686: return "oil filter"; break;
	case 687: return "organ"; break;
	case 688: return "oscilloscope"; break;
	//case 689: return "overskirt"; break;
	case 690: return "oxcart"; break;
	case 691: return "oxygen mask"; break;
	case 692: return "packet"; break;
	case 693: return "paddle"; break;
	case 694: return "paddlewheel"; break;
	case 695: return "padlock"; break;
	case 696: return "paintbrush"; break;
	//case 697: return "pajama"; break;
	case 698: return "palace"; break;
	case 699: return "panpipe"; break;
	case 700: return "paper towel"; break;
	case 701: return "parachute"; break;
	case 702: return "parallel bars"; break;
	case 703: return "park bench"; break;
	case 704: return "parking meter"; break;
	case 705: return "passenger car"; break;
	case 706: return "patio"; break;
	case 707: return "pay-phone"; break;
	case 708: return "pedestal"; break;
	case 709: return "pencil box"; break;
	case 710: return "pencil sharpener"; break;
	case 711: return "perfume"; break;
	case 712: return "Petri dish"; break;
	case 713: return "photocopier"; break;
	case 714: return "pick"; break;
	case 715: return "pickelhaube"; break;
	case 716: return "picket fence"; break;
	case 717: return "pickup"; break;
	case 718: return "pier"; break;
	case 719: return "piggy bank"; break;
	case 720: return "pill bottle"; break;
	case 721: return "pillow"; break;
	case 722: return "ping-pong ball"; break;
	case 723: return "pinwheel"; break;
	case 724: return "pirate"; break;
	case 725: return "pitcher"; break;
	case 726: return "plane"; break;
	case 727: return "planetarium"; break;
	case 728: return "plastic bag"; break;
	case 729: return "plate rack"; break;
	case 730: return "plow"; break;
	case 731: return "plunger"; break;
	case 732: return "Polaroid camera"; break;
	case 733: return "pole"; break;
	case 734: return "police van"; break;
	//case 735: return "poncho"; break;
	case 736: return "pool table"; break;
	case 737: return "pop bottle"; break;
	case 738: return "pot"; break;
	case 739: return "potter wheel"; break;
	case 740: return "power drill"; break;
	case 741: return "prayer rug"; break;
	case 742: return "printer"; break;
	case 743: return "prison"; break;
	case 744: return "projectile"; break;
	case 745: return "projector"; break;
	case 746: return "puck"; break;
	case 747: return "punching bag"; break;
	case 748: return "purse"; break;
	case 749: return "quill"; break;
	case 750: return "quilt"; break;
	case 751: return "racer"; break;
	case 752: return "racket"; break;
	case 753: return "radiator"; break;
	case 754: return "radio"; break;
	case 755: return "radio telescope"; break;
	case 756: return "rain barrel"; break;
	case 757: return "recreational vehicle"; break;
	case 758: return "reel"; break;
	case 759: return "reflex camera"; break;
	case 760: return "refrigerator"; break;
	case 761: return "remote control"; break;
	case 762: return "restaurant"; break;
	case 763: return "revolver"; break;
	case 764: return "rifle"; break;
	case 765: return "rocking chair"; break;
	case 766: return "rotisserie"; break;
	case 767: return "rubber eraser"; break;
	case 768: return "rugby ball"; break;
	case 769: return "rule"; break;
	case 770: return "running shoe"; break;
	case 771: return "safe"; break;
	case 772: return "safety pin"; break;
	case 773: return "saltshaker"; break;
	case 774: return "sandal"; break;
	case 775: return "sarong"; break;
	case 776: return "sax"; break;
	case 777: return "scabbard"; break;
	case 778: return "scale"; break;
	case 779: return "school bus"; break;
	case 780: return "schooner"; break;
	case 781: return "scoreboard"; break;
	case 782: return "screen"; break;
	case 783: return "screw"; break;
	case 784: return "screwdriver"; break;
	//case 785: return "seat belt"; break;
	case 786: return "sewing machine"; break;
	case 787: return "shield"; break;
	case 788: return "shoe shop"; break;
	case 789: return "shoji"; break;
	case 790: return "shopping basket"; break;
	case 791: return "shopping cart"; break;
	case 792: return "shovel"; break;
	case 793: return "shower cap"; break;
	case 794: return "shower curtain"; break;
	case 795: return "ski"; break;
	//case 796: return "ski mask"; break;
	case 797: return "sleeping bag"; break;
	case 798: return "slide rule"; break;
	case 799: return "sliding door"; break;
	case 800: return "slot"; break;
	case 801: return "snorkel"; break;
	case 802: return "snowmobile"; break;
	case 803: return "snowplow"; break;
	case 804: return "soap dispenser"; break;
	case 805: return "soccer ball"; break;
	case 806: return "sock"; break;
	case 807: return "solar dish"; break;
	case 808: return "sombrero"; break;
	case 809: return "soup bowl"; break;
	case 810: return "space bar"; break;
	case 811: return "space heater"; break;
	case 812: return "space shuttle"; break;
	case 813: return "spatula"; break;
	case 814: return "speedboat"; break;
	case 815: return "spider web"; break;
	case 816: return "spindle"; break;
	case 817: return "sports car"; break;
	case 818: return "spotlight"; break;
	case 819: return "stage"; break;
	case 820: return "steam locomotive"; break;
	case 821: return "steel arch bridge"; break;
	case 822: return "steel drum"; break;
	case 823: return "stethoscope"; break;
	//case 824: return "stole"; break;
	case 825: return "stone wall"; break;
	case 826: return "stopwatch"; break;
	case 827: return "stove"; break;
	case 828: return "strainer"; break;
	case 829: return "streetcar"; break;
	case 830: return "stretcher"; break;
	case 831: return "studio couch"; break;
	case 832: return "stupa"; break;
	case 833: return "submarine"; break;
	//case 834: return "suit"; break;
	case 835: return "sundial"; break;
	//case 836: return "sunglass"; break;
	//case 837: return "sunglasses"; break;
	case 838: return "sunscreen"; break;
	case 839: return "suspension bridge"; break;
	case 840: return "swab"; break;
	//case 841: return "sweatshirt"; break;
	case 842: return "swimming trunks"; break;
	case 843: return "swing"; break;
	case 844: return "switch"; break;
	case 845: return "syringe"; break;
	case 846: return "table lamp"; break;
	case 847: return "tank"; break;
	case 848: return "tape player"; break;
	case 849: return "teapot"; break;
	//case 850: return "teddy"; break;
	case 851: return "television"; break;
	case 852: return "tennis ball"; break;
	case 853: return "thatch"; break;
	case 854: return "theater curtain"; break;
	case 855: return "thimble"; break;
	case 856: return "thresher"; break;
	case 857: return "throne"; break;
	case 858: return "tile roof"; break;
	case 859: return "toaster"; break;
	case 860: return "tobacco shop"; break;
	case 861: return "toilet seat"; break;
	case 862: return "torch"; break;
	case 863: return "totem pole"; break;
	case 864: return "tow truck"; break;
	case 865: return "toyshop"; break;
	case 866: return "tractor"; break;
	case 867: return "trailer truck"; break;
	case 868: return "tray"; break;
	//case 869: return "trench coat"; break;
	case 870: return "tricycle"; break;
	case 871: return "trimaran"; break;
	case 872: return "tripod"; break;
	case 873: return "triumphal arch"; break;
	case 874: return "trolleybus"; break;
	case 875: return "trombone"; break;
	case 876: return "tub"; break;
	case 877: return "turnstile"; break;
	case 878: return "typewriter keyboard"; break;
	case 879: return "umbrella"; break;
	case 880: return "unicycle"; break;
	case 881: return "upright"; break;
	case 882: return "vacuum"; break;
	case 883: return "vase"; break;
	case 884: return "vault"; break;
	case 885: return "velvet"; break;
	case 886: return "vending machine"; break;
	//case 887: return "vestment"; break;
	case 888: return "viaduct"; break;
	case 889: return "violin"; break;
	case 890: return "volleyball"; break;
	case 891: return "waffle iron"; break;
	case 892: return "wall clock"; break;
	case 893: return "wallet"; break;
	case 894: return "wardrobe"; break;
	case 895: return "warplane"; break;
	case 896: return "washbasin"; break;
	case 897: return "washer"; break;
	case 898: return "water bottle"; break;
	case 899: return "water jug"; break;
	case 900: return "water tower"; break;
	case 901: return "whiskey jug"; break;
	case 902: return "whistle"; break;
	//case 903: return "wig"; break;
	case 904: return "window screen"; break;
	case 905: return "window shade"; break;
	//case 906: return "Windsor tie"; break;
	case 907: return "wine bottle"; break;
	case 908: return "wing"; break;
	case 909: return "wok"; break;
	case 910: return "wooden spoon"; break;
	case 911: return "wool"; break;
	case 912: return "worm fence"; break;
	case 913: return "wreck"; break;
	case 914: return "yawl"; break;
	case 915: return "yurt"; break;
	case 916: return "web site"; break;
	case 917: return "comic book"; break;
	case 918: return "crossword puzzle"; break;
	case 919: return "street sign"; break;
	case 920: return "traffic light"; break;
	case 921: return "book jacket"; break;
	case 922: return "menu"; break;
	case 923: return "plate"; break;
	case 924: return "guacamole"; break;
	case 925: return "consomme"; break;
	case 926: return "hot pot"; break;
	case 927: return "trifle"; break;
	case 928: return "ice cream"; break;
	case 929: return "ice lolly"; break;
	case 930: return "French loaf"; break;
	case 931: return "bagel"; break;
	case 932: return "pretzel"; break;
	case 933: return "cheeseburger"; break;
	case 934: return "hotdog"; break;
	case 935: return "mashed potato"; break;
	case 936: return "head cabbage"; break;
	case 937: return "broccoli"; break;
	case 938: return "cauliflower"; break;
	case 939: return "zucchini"; break;
	case 940: return "spaghetti squash"; break;
	case 941: return "acorn squash"; break;
	case 942: return "butternut squash"; break;
	case 943: return "cucumber"; break;
	case 944: return "artichoke"; break;
	case 945: return "bell pepper"; break;
	case 946: return "cardoon"; break;
	case 947: return "mushroom"; break;
	case 948: return "Granny Smith"; break;
	case 949: return "strawberry"; break;
	case 950: return "orange"; break;
	case 951: return "lemon"; break;
	case 952: return "fig"; break;
	case 953: return "pineapple"; break;
	case 954: return "banana"; break;
	case 955: return "jackfruit"; break;
	case 956: return "custard apple"; break;
	case 957: return "pomegranate"; break;
	case 958: return "hay"; break;
	case 959: return "carbonara"; break;
	case 960: return "chocolate sauce"; break;
	case 961: return "dough"; break;
	case 962: return "meat loaf"; break;
	case 963: return "pizza"; break;
	case 964: return "potpie"; break;
	case 965: return "burrito"; break;
	case 966: return "red wine"; break;
	case 967: return "espresso"; break;
	case 968: return "cup"; break;
	case 969: return "eggnog"; break;
	case 970: return "alp"; break;
	case 971: return "bubble"; break;
	case 972: return "cliff"; break;
	case 973: return "coral reef"; break;
	case 974: return "geyser"; break;
	case 975: return "lakeside"; break;
	case 976: return "promontory"; break;
	case 977: return "sandbar"; break;
	case 978: return "seashore"; break;
	case 979: return "valley"; break;
	case 980: return "volcano"; break;
	case 981: return "ballplayer"; break;
	//case 982: return "groom"; break;
	//case 983: return "scuba diver"; break;
	case 984: return "rapeseed"; break;
	case 985: return "daisy"; break;
	case 986: return "yellow lady's slipper"; break;
	case 987: return "corn"; break;
	case 988: return "acorn"; break;
	case 989: return "hip"; break;
	case 990: return "buckeye"; break;
	case 991: return "coral fungus"; break;
	case 992: return "agaric"; break;
	case 993: return "gyromitra"; break;
	case 994: return "stinkhorn"; break;
	case 995: return "earthstar"; break;
	case 996: return "hen-of-the-woods"; break;
	case 997: return "bolete"; break;
	//case 998: return "ear"; break;
	case 999: return "toilet tissue"; break;
	default: return "unknown"; break;
	}
}



std::string Helper::MapImageClassNumberToImageClassStr(int ImageClass)
{
	switch (ImageClass)
	{

	case 414: return "college_bag.bmp"; break;
	case 898: return "waterbottle.bmp"; break;
	case 632: return "speakers.bmp"; break;
	case 636: return "handbag.bmp"; break;
	case 662: return "router.bmp"; break;
	case 527: return "desktop_computer.bmp"; break;
	case 681: return "laptop.bmp"; break;
	case 968: return "coffee_mug.bmp"; break;
	case 954: return "banana.bmp"; break;
	case 528: return "mobile.bmp"; break;
	case 620: return "laptop_mobile.bmp"; break;
	case 504: return "coffee_mug.bmp"; break;


	case 610 :
	case 608 :
	case 617 :
	case 652 :
	case 655 :
	case 697 :
	case 834 :
	case 836 :
	case 841 :
	case 850 :
	case 983 :
	case 456 :
	case 457 :
	case 515 :
	case 578 :
	case 643: return "person.bmp"; break;
	// Person Class Detection logic
	//case 420:
	//case 762:
	//case 578:
	//case 559:
	//case 513:
	//case 743:
	//case 876:
	//case 401:
	//case 836:
	//case 456:
	//case 869:
	//case 617:
	//case 400:
	//case 399:
	//case 889:
	//case 805:
	//case 851:
	//case 523:
	//case 703:
	//case 457:
	//case 731:
	//case 402:
	//case 830:
	//case 818:
	//case 768:
	//case 655:
	//case 837:
	//case 585:
	//case 697:
	//case 683:
	//case 542:
	//case 546:
	//case 515:
	//case 890:
	//case 593:
	//case 982:
	//case 608:
	//case 862:
	//case 981:
	//case 432:
	//case 610:
	//case 424:
	//case 430:
	//case 652:
	//case 650:
	//case 842:
	//case 834:
	//case 916:
	//case 819: return "person.bmp"; break;

	default: return "Unknown.bmp";
	}
}