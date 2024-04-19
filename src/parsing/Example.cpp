/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Example.cpp
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

// This example reads the configuration file 'example.cfg' and displays
// some of its contents.

int example(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  libconfig::Config cfg;

  // Read the file. If there is an error, report it and exit.
  try
  {
    cfg.readFile("example.cfg");
  }
  catch(const libconfig::FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const libconfig::ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }

  // Get the store name.
  try
  {
    std::string name = cfg.lookup("name");
    std::cout << "Store name: " << name << std::endl << std::endl;
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    std::cerr << "No 'name' setting in configuration file." << std::endl;
  }

  const libconfig::Setting& root = cfg.getRoot();

  // Output a list of all books in the inventory.
  try
  {
    const libconfig::Setting &books = root["inventory"]["books"];
    int count = books.getLength();

    std::cout << std::setw(30) << std::left << "TITLE" << "  "
         << std::setw(30) << std::left << "AUTHOR" << "   "
         << std::setw(6) << std::left << "PRICE" << "  "
         << "QTY"
         << std::endl;

    for(int i = 0; i < count; ++i)
    {
      const libconfig::Setting &book = books[i];

      // Only output the record if all of the expected fields are present.
      std::string title, author;
      double price;
      int qty;

      if(!(book.lookupValue("title", title)
           && book.lookupValue("author", author)
           && book.lookupValue("price", price)
           && book.lookupValue("qty", qty)))
        continue;

      std::cout << std::setw(30) << std::left << title << "  "
           << std::setw(30) << std::left << author << "  "
           << '$' << std::setw(6) << std::right << price << "  "
           << qty
           << std::endl;
    }
    std::cout << std::endl;
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    // Ignore.
  }

  // Output a list of all books in the inventory.
  try
  {
    const libconfig::Setting &movies = root["inventory"]["movies"];
    int count = movies.getLength();

    std::cout << std::setw(30) << std::left << "TITLE" << "  "
         << std::setw(10) << std::left << "MEDIA" << "   "
         << std::setw(6) << std::left << "PRICE" << "  "
         << "QTY"
         << std::endl;

    for(int i = 0; i < count; ++i)
    {
      const libconfig::Setting &movie = movies[i];

      // Only output the record if all of the expected fields are present.
      std::string title, media;
      double price;
      int qty;

      if(!(movie.lookupValue("title", title)
           && movie.lookupValue("media", media)
           && movie.lookupValue("price", price)
           && movie.lookupValue("qty", qty)))
        continue;

      std::cout << std::setw(30) << std::left << title << "  "
           << std::setw(10) << std::left << media << "  "
           << '$' << std::setw(6) << std::right << price << "  "
           << qty
           << std::endl;
    }
    std::cout << std::endl;
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    // Ignore.
  }

  return(EXIT_SUCCESS);
}