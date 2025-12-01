#include "TimeManager.h"

#include <algorithm>

USING_NS_CC;

// 获取 TimeManager 的单例
TimeManager* TimeManager::getInstance() {
    static TimeManager* instance = nullptr;
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

// 构造函数
TimeManager::TimeManager()
    : _timeInSeconds(INIT_HOUR),
      _day(INIT_DAY),
      _hour(INIT_HOUR),
      _minute(INIT_MIN),
      _season(INIT_SEASON),
      _weather(INIT_WEATHER),
      _isDay(INIT_IS_DAY) {
    // 初始化时间（从第 INIT_DAY 天 INIT_HOUR:INIT_MIN 开始）
    updateTime();
}

// 析构函数
TimeManager::~TimeManager() {
    // 如有需要，可在此处清理资源
}

// 更新时间
void TimeManager::update(int deltaT) {
    // 记录更新前的时间与季节，用于触发 Observer 通知
    int oldDay = _day;
    int oldHour = _hour;
    int oldMinute = _minute;
    Season oldSeason = _season;

    // 推进游戏时间
    _timeInSeconds += deltaT;

    // 防止 timeInSeconds 过大，使用模运算形成循环时间
    _timeInSeconds %= (HOURS_IN_A_DAY * DAYS_IN_A_YEAR);

    updateTime();
    updateDayNightCycle();
    updateSeason();

    // 根据变化触发通知
    if (_day != oldDay) {
        notifyDayChanged(_day);
    }
    if (_season != oldSeason) {
        notifySeasonChanged(_season);
    }
    if (_hour != oldHour || _minute != oldMinute) {
        notifyTimeChanged(_hour, _minute);
    }
}

// 获取当前星期几
std::string TimeManager::getWeekDay() const {
    std::string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    return weekDays[(_day - 1) % DAYS_IN_A_WEEK];
}

// 获取当前时间（小时:分钟）
std::string TimeManager::getCurrentTime() const {
    return StringUtils::format("%02d:%02d", _hour, _minute);
}

// 获取当前季节
Season TimeManager::getCurrentSeason() const {
    return _season;
}

// 获取当前季节字符串
std::string TimeManager::getCurrentSeasonStr() const {
    switch (_season) {
    case Spring:
        return "Spr";
    case Summer:
        return "Sum";
    case Fall:
        return "Aut";
    case Winter:
        return "Win";
    default:
        return "Unknown";
    }
}

// 获取当前天数
int TimeManager::getCurrentDay() const {
    return _day;
}

// 更新昼夜状态
void TimeManager::updateDayNightCycle() {
    _isDay = (_hour >= DAY_START && _hour < DAY_END);
}

// 获取当前天气
Weather TimeManager::getCurrentWeather() const {
    return _weather;
}

// 获取当前天气字符串
std::string TimeManager::getCurrentWeatherStr() const {
    switch (_weather) {
    case Sunny:
        return "Sunny";
    case Rainy:
        return "Rainy";
    case Dry:
        return "Dry";
    default:
        return "Unknown";
    }
}

// 是否为白天
bool TimeManager::isDaytime() const {
    return _isDay;
}

// 开始时间更新
void TimeManager::startUpdating() {
    auto scheduler = Director::getInstance()->getScheduler();

    scheduler->schedule([this](float /*deltaTime*/) {
        // 这里简单地将 1 看作一个时间步长，可以根据需要调整
        update(1);
    }, this, 1.0f, false, "timeUpdateKey");
}

// 停止时间更新
void TimeManager::stopUpdating() {
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("timeUpdateKey", this);
}

// 计算当前小时/分钟/天数
void TimeManager::updateTime() {
    _hour = _timeInSeconds % HOURS_IN_A_DAY;
    _day = (_timeInSeconds / HOURS_IN_A_DAY) + 1;
    _minute = 0;

    // 同步更新昼夜状态
    _isDay = (_hour >= DAY_START && _hour < DAY_END);

    // 每天凌晨更新天气
    if (_hour == 0 && _minute == 0) {
        updateWeather();
    }
}

// 更新季节
void TimeManager::updateSeason() {
    // 每 DAYS_IN_A_SEASON 天变换一次季节
    _season = static_cast<Season>((_day - 1) / DAYS_IN_A_SEASON % 4);
}

// 随机更新天气
void TimeManager::updateWeather() {
    int weather = rand() % 100 + 1;
    if (weather < SUNNY_PROBABILITY * 100) {
        _weather = Sunny;
    }
    else if (weather < (RAINY_PROBABILITY + SUNNY_PROBABILITY) * 100) {
        _weather = Rainy;
    }
    else if (weather < (DRY_PROBABILITY + RAINY_PROBABILITY + SUNNY_PROBABILITY) * 100) {
        _weather = Dry;
    }
}

// Observer 注册
void TimeManager::attach(TimeObserver* observer) {
    if (!observer) return;
    auto it = std::find(_observers.begin(), _observers.end(), observer);
    if (it == _observers.end()) {
        _observers.push_back(observer);
    }
}

// Observer 注销
void TimeManager::detach(TimeObserver* observer) {
    if (!observer) return;
    _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}

// 通知天数变化
void TimeManager::notifyDayChanged(int day) {
    for (auto* observer : _observers) {
        if (observer) {
            observer->onDayChanged(day);
        }
    }
}

// 通知季节变化
void TimeManager::notifySeasonChanged(Season season) {
    for (auto* observer : _observers) {
        if (observer) {
            observer->onSeasonChanged(season);
        }
    }
}

// 通知时间变化
void TimeManager::notifyTimeChanged(int hour, int minute) {
    for (auto* observer : _observers) {
        if (observer) {
            observer->onTimeChanged(hour, minute);
        }
    }
}
