/*

#include <string>
#include <map>
// #include "RAINBOWCOLORS.h"

std::map <std::string, std::string> mapForegroundColor = 
{
  { "Red", "38;5;160" },
  { "Light Red", "38;5;196" },
  { "Orange", "38;5;202" },
  { "Yellow", "38;5;11" },
  { "Light Yellow", "38;5;226" },
  { "Green", "38;5;76" },
  { "Apple Green", "38;5;48" },
  { "Olive Green", "38;5;64" },
  { "Light Green", "38;5;107" },
  { "Neon Green", "38;5;120" },
  { "Blue", "38;5;20" },
  { "Sky Blue", "38;5;75" },
  { "Light Blue", "38;5;123" },
  { "Indigo", "38;5;18" },
  { "Violet", "38;5;128" },
  { "Pink", "38;5;161" },
  { "Black", "38;5;0" },
  { "Gray", "38;5;246" },
  { "Light Gray", "38;5;251" },
  { "White", "38;5;15" },
  { "Default", "39" }
};

std::map <std::string, std::string> mapBackgroundColor = 
{
  { "Red", "48;5;160" },
  { "Light Red", "48;5;196" },
  { "Orange", "48;5;202" },
  { "Yellow", "48;5;11" },
  { "Light Yellow", "48;5;226" },
  { "Green", "48;5;76" },
  { "Apple Green", "48;5;48" },
  { "Olive Green", "48;5;64" },
  { "Light Green", "48;5;107" },
  { "Neon Green", "48;5;120" },
  { "Blue", "48;5;20" },
  { "Sky Blue", "48;5;75" },
  { "Light Blue", "48;5;123" },
  { "Indigo", "48;5;18" },
  { "Violet", "48;5;128" },
  { "Pink", "48;5;161" },
  { "Black", "48;5;0" },
  { "Gray", "48;5;246" },
  { "Light Gray", "48;5;251" },
  { "White", "48;5;15" },
  { "Default", "49" }
};

std::map <std::string, std::string> mapSetFormat =
{
  { "Default", "0" },
  { "Bold", "1" },
  { "Underlined", "4" },
  { "Blink", "5" },
  { "Reverse", "7" },
  { "Hidden", "8" }
};

std::string RainbowText (   std::string src,
                            std::string foregroundColor = "Default"
                        )
{
  auto pairFound = mapForegroundColor.find(foregroundColor);
  if (pairFound != mapForegroundColor.end())
      foregroundColor = pairFound->first;
  else
      foregroundColor = "Default";

  std::string backgroundColor = "Default";
  std::string format = "Default";

  std::string const escCode = "\033";
  
  std::string formattedText = escCode  + "[" +
                mapSetFormat.at(format) + ";" +
                mapForegroundColor.at(foregroundColor) + ";" +
                mapBackgroundColor.at(backgroundColor) + "m" +
                src + escCode + "[0m";
  return formattedText;
}

std::string RainbowText (   std::string src,
                            std::string foregroundColor = "Default",
                            std::string backgroundColor = "Default"
                        )
{
  auto pairFound = mapForegroundColor.find(foregroundColor);
  if (pairFound != mapForegroundColor.end())
      foregroundColor = pairFound->first;
  else
      foregroundColor = "Default";

  pairFound = mapBackgroundColor.find(backgroundColor);
  if (pairFound != mapBackgroundColor.end())
      backgroundColor = pairFound->first;
  else
      backgroundColor = "Default";
      
  std::string format = "Default";

  std::string const escCode = "\033";
  
  std::string formattedText = escCode  + "[" +
                mapSetFormat.at(format) + ";" +
                mapForegroundColor.at(foregroundColor) + ";" +
                mapBackgroundColor.at(backgroundColor) + "m" +
                src + escCode + "[0m";
  return formattedText;
}

std::string RainbowText ( std::string src,
                          std::string foregroundColor = "Default",
                          std::string backgroundColor = "Default",
                          std::string format = "Default"
                        )
{
  auto pairFound = mapForegroundColor.find(foregroundColor);
  if (pairFound != mapForegroundColor.end())
      foregroundColor = pairFound->first;
  else
      foregroundColor = "Default";

  pairFound = mapBackgroundColor.find(backgroundColor);
  if (pairFound != mapBackgroundColor.end())
      backgroundColor = pairFound->first;
  else
      backgroundColor = "Default";

  pairFound = mapSetFormat.find(format);
  if (pairFound != mapSetFormat.end())
      format = pairFound->first;
  else
      format = "Default";

  std::string const escCode = "\033";
  
  std::string formattedText = escCode  + "[" +
                mapSetFormat.at(format) + ";" +
                mapForegroundColor.at(foregroundColor) + ";" +
                mapBackgroundColor.at(backgroundColor) + "m" +
                src + escCode + "[0m";
  return formattedText;
}

*/