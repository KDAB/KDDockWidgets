import 'package:flutter/material.dart';

// ignore: must_be_immutable
class MyWidget extends StatelessWidget {
  static int nextImageId = 0;
  final int imageId;
  MyWidget({super.key}) : imageId = nextImageId {
    MyWidget.nextImageId++;
  }

  String imageName() {
    switch (imageId % 2) {
      case 0:
        return 'assets/KDAB_bubble_fulcolor.png';
      case 1:
        return 'assets/KDAB_bubble_blue.png';
    }

    return 'assets/KDAB_bubble_fulcolor.png';
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.white,
      padding: const EdgeInsets.all(40.0),
      child: Image.asset(
        imageName(),
        fit: BoxFit.cover,
      ),
    );
  }
}
