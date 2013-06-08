/*
  ==============================================================================

    CustomLF.h
    Created: 6 Jun 2013 9:41:32pm
    Author:  hemmer

  ==============================================================================
*/

#ifndef __CUSTOMLF_H_59A980C8__
#define __CUSTOMLF_H_59A980C8__


/*
==============================================================================

CustomLF.cpp
Created: 6 Jun 2013 9:41:32pm
Author:  hemmer

==============================================================================
*/

#include "CustomLF.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "FreeTypeFaces.h"




class CustomLookAndFeel : public LookAndFeel
{
public:
	CustomLookAndFeel()
	{
		// Add the TrueType font "Helvetica Neue LT Com 65 Medium" and
		// use hinting when the font height is between 7 and 12 inclusive.
		FreeTypeFaces::addFaceFromMemory(
			7.f, 12.f, true,
			BinaryData::slkscr_ttf, BinaryData::slkscr_ttfSize);
//			BinaryData::visitor1_ttf,
//			BinaryData::visitor1_ttfSize);

	}


	void drawLabel(Graphics& g, Label& label)
	{
		// set up the font with the right size
		//Font font(label.getFont());
		//font.setHeight(silkFontSizeSmall);
		g.setFont(Font (10.f));


		g.fillAll (label.findColour(Label::backgroundColourId));

		const float alpha = label.isEnabled() ? 1.0f : 0.5f;

		g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
		g.drawFittedText(label.getText(), 4, 4,
			label.getWidth() - 2, label.getHeight() - 8,
			Justification::centredLeft, 1, 1.0f);


		g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
		g.drawRect (0, 0, label.getWidth(), label.getHeight());

	}



	const Typeface::Ptr getTypefaceForFont (Font const& font)
	{
		Typeface::Ptr tf;
		String faceName (font.getTypefaceName());

		// Make requests for the default sans serif font use our
		// FreeType hinted font instead.
		if (faceName == Font::getDefaultSansSerifFontName())
		{
			DBG(faceName);


			// Create a new Font identical to the old one, then
			// switch the name to our hinted font.
			Font f (font);
			// You'll need to know the exact name embedded in the font. There
			// are a variety of free programs for retrieving this information.
			f.setTypefaceName ("Silkscreen");

			DBG(f.getTypefaceName());

			// Now get the hinted typeface.
			tf = FreeTypeFaces::createTypefaceForFont (f);
		}
		// If we got here without creating a new typeface
		// then just use the default LookAndFeel behavior.
		if (!tf)
			tf = LookAndFeel::getTypefaceForFont (font);
		return tf;
	}
};


#endif  // __CUSTOMLF_H_59A980C8__
