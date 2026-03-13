#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "backend/models/Zodiac.h"
#include "crow.h"
#include "crow/middlewares/cors.h"

using namespace std;

// ═══════════════════════════════════════════
// ZODIAC DATABASE
// ═══════════════════════════════════════════
map<string, Zodiac> zodiacDB = {
    {"Aries",       Zodiac("Aries",       "Fire",  "Mars",    "Confident, bold, energetic leader.")},
    {"Taurus",      Zodiac("Taurus",      "Earth", "Venus",   "Reliable, patient, practical.")},
    {"Gemini",      Zodiac("Gemini",      "Air",   "Mercury", "Curious, adaptable communicator.")},
    {"Cancer",      Zodiac("Cancer",      "Water", "Moon",    "Emotional, intuitive and caring.")},
    {"Leo",         Zodiac("Leo",         "Fire",  "Sun",     "Proud, generous, charismatic.")},
    {"Virgo",       Zodiac("Virgo",       "Earth", "Mercury", "Analytical, hardworking.")},
    {"Libra",       Zodiac("Libra",       "Air",   "Venus",   "Diplomatic, fair-minded.")},
    {"Scorpio",     Zodiac("Scorpio",     "Water", "Pluto",   "Resourceful, brave.")},
    {"Sagittarius", Zodiac("Sagittarius", "Fire",  "Jupiter", "Adventurous, optimistic.")},
    {"Capricorn",   Zodiac("Capricorn",   "Earth", "Saturn",  "Disciplined, responsible.")},
    {"Aquarius",    Zodiac("Aquarius",    "Air",   "Uranus",  "Progressive, independent.")},
    {"Pisces",      Zodiac("Pisces",      "Water", "Neptune", "Compassionate, artistic.")}
};

map<string, string> symbolsDB = {
    {"Aries","♈"},{"Taurus","♉"},{"Gemini","♊"},{"Cancer","♋"},
    {"Leo","♌"},{"Virgo","♍"},{"Libra","♎"},{"Scorpio","♏"},
    {"Sagittarius","♐"},{"Capricorn","♑"},{"Aquarius","♒"},{"Pisces","♓"}
};

map<string, string> careersDB = {
    {"Aries","Leader, Entrepreneur, Army Officer"},{"Taurus","Banker, Architect, Designer"},
    {"Gemini","Journalist, Writer, Marketing"},{"Cancer","Doctor, Nurse, Social Worker"},
    {"Leo","Actor, Politician, Manager"},{"Virgo","Analyst, Scientist, Teacher"},
    {"Libra","Lawyer, Diplomat, Artist"},{"Scorpio","Detective, Surgeon, Researcher"},
    {"Sagittarius","Professor, Philosopher, Traveler"},{"Capricorn","CEO, Engineer, Administrator"},
    {"Aquarius","Innovator, Scientist, Programmer"},{"Pisces","Musician, Poet, Photographer"}
};

map<string, string> horoscope = {
    {"Aries","Today is a great day to take initiative. Trust your instincts."},
    {"Taurus","Focus on stability today. Small steps bring big rewards."},
    {"Gemini","Communication will open new opportunities today."},
    {"Cancer","Emotional balance will help you make the right decisions."},
    {"Leo","Your confidence attracts attention today. Lead with kindness."},
    {"Virgo","A productive day ahead. Stay organized and focused."},
    {"Libra","Seek harmony in conversations today."},
    {"Scorpio","Your determination will help you overcome obstacles."},
    {"Sagittarius","Adventure and curiosity guide you today."},
    {"Capricorn","Hard work today brings long-term rewards."},
    {"Aquarius","Creative ideas will inspire those around you."},
    {"Pisces","Trust your intuition and follow your dreams."}
};

map<string, string> compatibility = {
    {"Aries-Leo","Excellent match 🔥 Passionate and energetic"},
    {"Aries-Sagittarius","Great match 🔥 Adventurous fire signs"},
    {"Aries-Gemini","Fun relationship 🌪 Energetic and social"},
    {"Aries-Cancer","Challenging match ⚡ Emotional differences"},
    {"Taurus-Virgo","Very stable match 🌱 Loyal and grounded"},
    {"Taurus-Capricorn","Power couple 💼 Practical and ambitious"},
    {"Taurus-Cancer","Strong emotional bond 💧"},
    {"Taurus-Leo","Difficult match ⚡ Strong personalities"},
    {"Gemini-Libra","Perfect intellectual match 🌬"},
    {"Gemini-Aquarius","Creative and exciting relationship"},
    {"Gemini-Aries","Energetic and spontaneous"},
    {"Gemini-Scorpio","Difficult emotional balance"},
    {"Cancer-Pisces","Deep emotional connection 💙"},
    {"Cancer-Scorpio","Powerful emotional bond"},
    {"Cancer-Taurus","Stable and nurturing relationship"},
    {"Cancer-Aries","Clashing personalities"},
    {"Leo-Aries","Power couple 🔥 Strong leadership"},
    {"Leo-Sagittarius","Adventurous fire connection"},
    {"Leo-Libra","Fun social energy"},
    {"Leo-Taurus","Stubborn personalities"},
    {"Virgo-Taurus","Very stable earth connection"},
    {"Virgo-Capricorn","Highly compatible practical match"},
    {"Virgo-Cancer","Supportive emotional balance"},
    {"Virgo-Gemini","Different life perspectives"},
    {"Libra-Gemini","Great communication"},
    {"Libra-Aquarius","Creative air sign connection"},
    {"Libra-Sagittarius","Romantic and supportive"},
    {"Libra-Cancer","Emotional imbalance sometimes"},
    {"Scorpio-Cancer","Deep emotional loyalty"},
    {"Scorpio-Pisces","Intuitive spiritual connection"},
    {"Scorpio-Capricorn","Strong ambitious partnership"},
    {"Scorpio-Gemini","Different emotional depths"},
    {"Sagittarius-Aries","Explosive adventurous match"},
    {"Sagittarius-Leo","Fire signs with huge energy"},
    {"Sagittarius-Aquarius","Free-spirited connection"},
    {"Sagittarius-Virgo","Different lifestyles"},
    {"Sagittarius-Pisces","Romantic and supportive"},
    {"Capricorn-Taurus","Very stable and loyal"},
    {"Capricorn-Virgo","Practical and intelligent match"},
    {"Capricorn-Scorpio","Power couple energy"},
    {"Capricorn-Aries","Clashing leadership styles"},
    {"Aquarius-Gemini","Creative and intellectual"},
    {"Aquarius-Libra","Strong air sign harmony"},
    {"Aquarius-Sagittarius","Adventurous thinkers"},
    {"Aquarius-Taurus","Different values sometimes"},
    {"Pisces-Cancer","Very emotional connection"},
    {"Pisces-Scorpio","Deep intuitive relationship"},
    {"Pisces-Sagittarius","Romantic and supportive"},
    {"Pisces-Gemini","Different emotional needs"}
};

// ═══════════════════════════════════════════
// LUCKY NUMBER DATA
// ═══════════════════════════════════════════
map<string, vector<int>> luckyNumbersDB = {
    {"Aries",{1,8,17}},{"Taurus",{2,6,15}},{"Gemini",{3,12,21}},
    {"Cancer",{2,7,16}},{"Leo",{1,4,19}},{"Virgo",{5,14,23}},
    {"Libra",{6,15,24}},{"Scorpio",{8,11,18}},{"Sagittarius",{3,9,27}},
    {"Capricorn",{4,8,22}},{"Aquarius",{7,11,29}},{"Pisces",{6,10,12}}
};

map<string, string> luckyMessageDB = {
    {"Aries","Your fire energy aligns with bold, powerful numbers today."},
    {"Taurus","Grounded and steady — your numbers bring material comfort."},
    {"Gemini","Curious and dynamic, your lucky numbers open doors to conversation."},
    {"Cancer","Your intuition is heightened — trust these numbers today."},
    {"Leo","The universe shines on you. Let these numbers lead the way."},
    {"Virgo","Precision is your strength. These numbers reward careful action."},
    {"Libra","Balance and beauty align with your lucky numbers today."},
    {"Scorpio","Deep and powerful energy surrounds these numbers for you."},
    {"Sagittarius","Adventure awaits — your lucky numbers point to new horizons."},
    {"Capricorn","Discipline meets fortune. These numbers reward your hard work."},
    {"Aquarius","Innovation and vision guide your numbers today."},
    {"Pisces","Your dreamy nature connects deeply with these mystical numbers."}
};

// ═══════════════════════════════════════════
// LUCKY COLOUR DATA
// ═══════════════════════════════════════════
struct LuckyColour { string name, hex, meaning; };

map<string, vector<LuckyColour>> luckyColourDB = {
    {"Aries",      {{"Red","#e63946","Passion and courage"},{"Orange","#f4845f","Energy and enthusiasm"},{"White","#f1faee","Clarity and new beginnings"}}},
    {"Taurus",     {{"Green","#2d6a4f","Growth and stability"},{"Pink","#f4a5b0","Love and comfort"},{"White","#f1faee","Purity and peace"}}},
    {"Gemini",     {{"Yellow","#f9c74f","Intellect and joy"},{"Light Blue","#90e0ef","Communication and clarity"},{"Green","#52b788","Adaptability"}}},
    {"Cancer",     {{"Silver","#adb5bd","Intuition and emotion"},{"White","#f8f9fa","Protection and calm"},{"Sea Green","#52b788","Healing and nurturing"}}},
    {"Leo",        {{"Gold","#c9a84c","Royalty and power"},{"Orange","#f4845f","Vitality and warmth"},{"Purple","#9b5de5","Luxury and ambition"}}},
    {"Virgo",      {{"Green","#2d6a4f","Health and harmony"},{"Brown","#8d6748","Groundedness"},{"Grey","#adb5bd","Precision and calm"}}},
    {"Libra",      {{"Pink","#f4a5b0","Romance and grace"},{"Blue","#4361ee","Balance and truth"},{"Lavender","#c8b6e2","Peace and diplomacy"}}},
    {"Scorpio",    {{"Deep Red","#9b2226","Intensity and power"},{"Black","#333333","Mystery and depth"},{"Maroon","#6a0572","Transformation"}}},
    {"Sagittarius",{{"Purple","#9b5de5","Wisdom and adventure"},{"Blue","#4361ee","Freedom and vision"},{"Yellow","#f9c74f","Optimism"}}},
    {"Capricorn",  {{"Brown","#8d6748","Stability and earth"},{"Black","#333333","Discipline and focus"},{"Dark Green","#1b4332","Ambition"}}},
    {"Aquarius",   {{"Electric Blue","#00b4d8","Innovation and freedom"},{"Turquoise","#2ec4b6","Originality"},{"Violet","#7b5ea7","Vision"}}},
    {"Pisces",     {{"Sea Blue","#48cae4","Depth and dreams"},{"Lavender","#c8b6e2","Spirituality"},{"Aquamarine","#80ffdb","Healing and flow"}}}
};

// ═══════════════════════════════════════════
// TAROT DECK
// ═══════════════════════════════════════════
struct TarotCard { string name, symbol, meaning, advice; };

vector<TarotCard> tarotDeck = {
    {"The Fool","🃏","New beginnings, innocence, spontaneity","Embrace the unknown. A leap of faith will serve you well."},
    {"The Magician","✨","Willpower, skill, resourcefulness","You have all the tools you need. Take action now."},
    {"The High Priestess","🌙","Intuition, mystery, inner knowledge","Trust your inner voice. The answers lie within."},
    {"The Empress","🌿","Fertility, abundance, nurturing","Nurture your creative projects. Growth is near."},
    {"The Emperor","👑","Authority, structure, leadership","Take charge and establish order in your life."},
    {"The Hierophant","⛪","Tradition, wisdom, spiritual guidance","Seek wisdom from a trusted mentor or tradition."},
    {"The Lovers","❤️","Love, harmony, relationships, choices","Follow your heart, but weigh your choices carefully."},
    {"The Chariot","🏆","Determination, control, victory","Push forward with confidence. Victory is yours."},
    {"Strength","🦁","Courage, patience, inner strength","Gentle persistence will overcome any obstacle."},
    {"The Hermit","🕯️","Introspection, solitude, guidance","Step back and reflect. Your answer comes from within."},
    {"Wheel of Fortune","🎡","Cycles, fate, turning points","Change is coming. Embrace the turning of the wheel."},
    {"Justice","⚖️","Fairness, truth, cause and effect","Act with integrity. The truth will come to light."},
    {"The Hanged Man","🔄","Suspension, surrender, new perspective","Pause and see things differently. Surrender brings clarity."},
    {"Death","🌑","Transformation, endings, new beginnings","Let go of what no longer serves you. Transformation awaits."},
    {"Temperance","🌊","Balance, patience, moderation","Find the middle path. Patience will bring harmony."},
    {"The Devil","⛓️","Bondage, addiction, shadow self","Break free from what holds you back. You have the power."},
    {"The Tower","⚡","Chaos, revelation, sudden change","Unexpected change brings ultimate freedom. Trust the process."},
    {"The Star","⭐","Hope, renewal, inspiration","Have faith. A bright and hopeful chapter is beginning."},
    {"The Moon","🌕","Illusion, fear, the unconscious","Not all is as it seems. Trust your instincts, not fears."},
    {"The Sun","☀️","Joy, success, vitality, clarity","Radiance and success surround you. Embrace this energy."},
    {"Judgement","🔔","Reflection, reckoning, awakening","A moment of truth and awakening is upon you."},
    {"The World","🌍","Completion, integration, accomplishment","You have reached a major milestone. Celebrate your journey."}
};

// ═══════════════════════════════════════════
// VASTU DATA
// ═══════════════════════════════════════════
struct VastuTip { string direction, icon, tip, element; };

map<string, vector<VastuTip>> vastuDB = {
    {"Aries",      {{"North","🧲","Place your work desk facing north to attract financial energy.","Water"},{"East","🌅","Keep the east entrance clean and well-lit for positive energy.","Fire"},{"South-West","🏡","Bedroom in south-west strengthens relationships and stability.","Earth"}}},
    {"Taurus",     {{"South-East","🔥","Kitchen in south-east brings health and prosperity.","Fire"},{"North","💰","Keep a green plant in the north to attract wealth.","Water"},{"Center","🌀","Keep the center of your home clutter-free for positive flow.","Space"}}},
    {"Gemini",     {{"North-West","🌬","Study or workspace in north-west enhances communication.","Air"},{"East","📚","Place bookshelves on the east wall for knowledge and growth.","Fire"},{"West","🌙","A west-facing window brings clarity and balanced thinking.","Water"}}},
    {"Cancer",     {{"North-East","🙏","Place a small prayer or meditation corner in north-east.","Water"},{"West","🌊","A water feature in the west enhances emotional well-being.","Water"},{"South-West","🛏️","Master bedroom in south-west for deep emotional security.","Earth"}}},
    {"Leo",        {{"East","☀️","Main entrance facing east brings fame and recognition.","Fire"},{"South","🏆","Display achievements and awards on the south wall.","Fire"},{"Center","👑","Keep the living room center spacious and grand.","Space"}}},
    {"Virgo",      {{"North","🧹","Keep the north zone spotless for mental clarity.","Water"},{"East","🌱","Fresh herbs or plants in the east promote health.","Fire"},{"South-West","📦","Organized storage in south-west reduces anxiety.","Earth"}}},
    {"Libra",      {{"North-West","🌸","Decorate north-west with pink or white flowers for harmony.","Air"},{"East","🪞","A mirror on the east wall doubles positive energy.","Fire"},{"Center","⚖️","Maintain balance and symmetry in your home decor.","Space"}}},
    {"Scorpio",    {{"North-East","🕯️","Light a candle in north-east for spiritual protection.","Water"},{"South","🔴","Use deep red accents in the south for intensity and power.","Fire"},{"Basement","🔒","Keep lower levels clean and secure for emotional stability.","Earth"}}},
    {"Sagittarius",{{"North-East","🗺️","Place maps or travel art in north-east for adventure energy.","Water"},{"East","🌄","Keep east windows unblocked for inspiration and freedom.","Fire"},{"West","📖","A library or study in the west supports wisdom and growth.","Water"}}},
    {"Capricorn",  {{"South-West","💼","Home office in south-west enhances career stability.","Earth"},{"North","🌿","A money plant in the north attracts financial growth.","Water"},{"South","🏔️","Earthy tones in the south room build grounded energy.","Fire"}}},
    {"Aquarius",   {{"North-West","💡","Innovation corner in north-west sparks creative ideas.","Air"},{"East","🔵","Use blue or turquoise tones in the east for clarity.","Fire"},{"Center","🌐","An open floor plan encourages free-thinking and progress.","Space"}}},
    {"Pisces",     {{"North-East","🙏","A water bowl or fountain in north-east brings spiritual calm.","Water"},{"West","🎨","Art studio or creative space in the west enhances imagination.","Water"},{"South-West","🌊","Soft blue tones in south-west promote emotional healing.","Earth"}}}
};

// ═══════════════════════════════════════════
// HELPERS
// ═══════════════════════════════════════════
string calculateZodiac(int day, int month) {
    if (month==1)  return (day<=19)?"Capricorn":"Aquarius";
    if (month==2)  return (day<=18)?"Aquarius":"Pisces";
    if (month==3)  return (day<=20)?"Pisces":"Aries";
    if (month==4)  return (day<=19)?"Aries":"Taurus";
    if (month==5)  return (day<=20)?"Taurus":"Gemini";
    if (month==6)  return (day<=20)?"Gemini":"Cancer";
    if (month==7)  return (day<=22)?"Cancer":"Leo";
    if (month==8)  return (day<=22)?"Leo":"Virgo";
    if (month==9)  return (day<=22)?"Virgo":"Libra";
    if (month==10) return (day<=22)?"Libra":"Scorpio";
    if (month==11) return (day<=21)?"Scorpio":"Sagittarius";
    if (month==12) return (day<=21)?"Sagittarius":"Capricorn";
    return "Unknown";
}

string normalizeSign(string sign) {
    transform(sign.begin(), sign.end(), sign.begin(), ::tolower);
    if (!sign.empty()) sign[0] = toupper(sign[0]);
    return sign;
}

// ═══════════════════════════════════════════
// MAIN SERVER
// ═══════════════════════════════════════════
int main() {
    srand(time(0));

    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .origin("*")
        .methods(crow::HTTPMethod::Get, crow::HTTPMethod::Post, crow::HTTPMethod::Options)
        .headers("Content-Type");

    // ── Root ──
    CROW_ROUTE(app, "/")
    ([]() { crow::response res; res.set_static_file_info("frontend/index.html"); return res; });

    // ── POST /get-sign ──
    CROW_ROUTE(app, "/get-sign").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");
        int day = body["day"].i(), month = body["month"].i();
        string sign = calculateZodiac(day, month);
        if (zodiacDB.count(sign)) {
            Zodiac z = zodiacDB[sign];
            crow::json::wvalue j;
            j["name"]=z.getName(); j["element"]=z.getElement();
            j["rulingPlanet"]=z.getRulingPlanet(); j["traits"]=z.getTraits();
            return crow::response(j.dump());
        }
        return crow::response(400, "Invalid Date");
    });

    // ── GET /sign ──
    CROW_ROUTE(app, "/sign")([](const crow::request &req) {
        auto name=req.url_params.get("name"), age=req.url_params.get("age");
        auto place=req.url_params.get("place");
        auto day_s=req.url_params.get("day"), mon_s=req.url_params.get("month");
        if (!day_s||!mon_s) return crow::response(400,"{\"error\":\"Missing date\"}");
        int day=stoi(day_s), month=stoi(mon_s);
        string sign=calculateZodiac(day,month);
        crow::json::wvalue res;
        res["name"]=name?name:""; res["age"]=age?age:"";
        res["place"]=place?place:""; res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        res["description"]=zodiacDB[sign].getTraits();
        return crow::response(res);
    });

    // ── GET /career ──
    CROW_ROUTE(app, "/career")([](const crow::request &req) {
        auto sp=req.url_params.get("sign");
        if (!sp) return crow::response(400,"{\"error\":\"Missing sign\"}");
        string sign=normalizeSign(string(sp));
        crow::json::wvalue res;
        res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        res["careers"]=careersDB.count(sign)?careersDB[sign]:"Explorer, Thinker, Creator";
        return crow::response(res);
    });

    // ── GET /horoscope/:sign ──
    CROW_ROUTE(app, "/horoscope/<string>")([](string sign) {
        sign=normalizeSign(sign);
        crow::json::wvalue res;
        res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        res["message"]=horoscope.count(sign)?horoscope[sign]:"No horoscope available.";
        return crow::response(res.dump());
    });

    // ── GET /compatibility/:s1/:s2 ──
    CROW_ROUTE(app, "/compatibility/<string>/<string>")([](string s1, string s2) {
        s1=normalizeSign(s1); s2=normalizeSign(s2);
        string key=s1+"-"+s2;
        crow::json::wvalue res;
        res["sign1"]=s1; res["sign2"]=s2;
        res["result"]=compatibility.count(key)?compatibility[key]:"Compatibility unknown 🤔";
        res["score"]=(s1[0]+s2[0])%40+60;
        return crow::response(res);
    });

    // ── GET /explore/:sign ──
    CROW_ROUTE(app, "/explore/<string>")([](string sign) {
        sign=normalizeSign(sign);
        if (zodiacDB.count(sign)) {
            Zodiac z=zodiacDB[sign];
            crow::json::wvalue j;
            j["name"]=z.getName(); j["element"]=z.getElement();
            j["rulingPlanet"]=z.getRulingPlanet(); j["traits"]=z.getTraits();
            return crow::response(j.dump());
        }
        return crow::response(404,"Sign Not Found");
    });

    // ════════════════════════════════════════
    // ── GET /lucky-number?sign=Aries ──
    // ════════════════════════════════════════
    CROW_ROUTE(app, "/lucky-number")([](const crow::request &req) {
        auto sp=req.url_params.get("sign");
        if (!sp) return crow::response(400,"{\"error\":\"Missing sign\"}");
        string sign=normalizeSign(string(sp));
        crow::json::wvalue res;
        res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        if (luckyNumbersDB.count(sign)) {
            auto& nums=luckyNumbersDB[sign];
            int today=nums[rand()%nums.size()];
            res["today"]=today;
            crow::json::wvalue::list nl;
            for (int n:nums) nl.push_back(n);
            res["numbers"]=std::move(nl);
            res["message"]=luckyMessageDB.count(sign)?luckyMessageDB[sign]:"The stars guide your numbers today.";
        } else {
            res["today"]=7;
            res["numbers"]=crow::json::wvalue::list{3,7,21};
            res["message"]="The stars guide your numbers today.";
        }
        return crow::response(res);
    });

    // ════════════════════════════════════════
    // ── GET /lucky-colour?sign=Aries ──
    // ════════════════════════════════════════
    CROW_ROUTE(app, "/lucky-colour")([](const crow::request &req) {
        auto sp=req.url_params.get("sign");
        if (!sp) return crow::response(400,"{\"error\":\"Missing sign\"}");
        string sign=normalizeSign(string(sp));
        crow::json::wvalue res;
        res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        if (luckyColourDB.count(sign)) {
            auto& colours=luckyColourDB[sign];
            crow::json::wvalue::list cl;
            for (auto& c:colours) {
                crow::json::wvalue item;
                item["name"]=c.name; item["hex"]=c.hex; item["meaning"]=c.meaning;
                cl.push_back(std::move(item));
            }
            res["colours"]=std::move(cl);
            res["primary"]=colours[0].name;
            res["primaryHex"]=colours[0].hex;
            res["primaryMeaning"]=colours[0].meaning;
        }
        return crow::response(res);
    });

    // ════════════════════════════════════════
    // ── GET /tarot?count=3 ──
    // ════════════════════════════════════════
    CROW_ROUTE(app, "/tarot")([](const crow::request &req) {
        auto cp=req.url_params.get("count");
        int count=cp?min(3,max(1,stoi(string(cp)))):1;
        crow::json::wvalue res;
        crow::json::wvalue::list drawn;
        vector<int> used;
        for (int i=0;i<count;i++) {
            int idx;
            do { idx=rand()%tarotDeck.size(); }
            while (find(used.begin(),used.end(),idx)!=used.end());
            used.push_back(idx);
            auto& card=tarotDeck[idx];
            crow::json::wvalue item;
            item["name"]=card.name; item["symbol"]=card.symbol;
            item["meaning"]=card.meaning; item["advice"]=card.advice;
            drawn.push_back(std::move(item));
        }
        res["cards"]=std::move(drawn);
        res["count"]=count;
        return crow::response(res);
    });

    // ════════════════════════════════════════
    // ── GET /vastu?sign=Aries ──
    // ════════════════════════════════════════
    CROW_ROUTE(app, "/vastu")([](const crow::request &req) {
        auto sp=req.url_params.get("sign");
        if (!sp) return crow::response(400,"{\"error\":\"Missing sign\"}");
        string sign=normalizeSign(string(sp));
        crow::json::wvalue res;
        res["sign"]=sign;
        res["symbol"]=symbolsDB.count(sign)?symbolsDB[sign]:"✦";
        if (vastuDB.count(sign)) {
            auto& tips=vastuDB[sign];
            crow::json::wvalue::list tl;
            for (auto& t:tips) {
                crow::json::wvalue item;
                item["direction"]=t.direction; item["icon"]=t.icon;
                item["tip"]=t.tip; item["element"]=t.element;
                tl.push_back(std::move(item));
            }
            res["tips"]=std::move(tl);
        }
        return crow::response(res);
    });

    // ── CATCH-ALL — MUST BE LAST ──
    CROW_ROUTE(app, "/<path>")([](std::string page) {
        crow::response res;
        res.set_static_file_info("frontend/"+page);
        return res;
    });

    app.port(8080).multithreaded().run();
}
