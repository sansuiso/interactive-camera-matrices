# Interactive camera matrices

Simple graphical application that renders a few squares in order to demonstrate the effect of the various coefficients of the camera matrices used in Computer Vision.

## Getting started

### Prerequisites

What you need to build and run the application:

* graphics driver: must support OpenGL 3.2 (core profile)
* [Qt](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/) in version >= 5
* [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/) as it is currently the only supported build system
* [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) installed in `/usr/local/include` is used for some matrix manipulation 

### Installing

Build and run after opening the project file in QtCreator.
You may want to tweak the .pro file to find your local install of Eigen3 in case of a different directory.

## Running the application

The application presents two modes: extrinsinc or intrinsic camera parameter modification.
Parameters are depicted according to their physical meaning (rotation angle around x-axis, pixel skew...).
Changes are applied live to a simple 3D scene and to a representation of the matrices K and R,T as they are classically called in Computer Vision.

## Running the tests

_TODO:_ add tests

## Deployment

_TODO_

## Built with

* [Qt](https://www.qt.io) for the cross-platform UI and OpenGL toolkit
* [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/) as primary IDE

## Contributing

Pull requests are welcome!

## Versioning

_TODO:_ add versions and tags

## Authors

* **Emmanuel d'Angelo** - *Initial work* - [website](https://www.computersdontsee.net/)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
