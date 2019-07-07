AMLEO Impl
// Topic: Parse (split) a string in C++ using string delimiter (standard C++)
// Source: https://stackoverflow.com/a/44495206
std::vector<std::string> splitString(
    std::string str,
    const std::string &delimiter
) {
    std::vector<std::string> result;
    std::size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        auto token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}
