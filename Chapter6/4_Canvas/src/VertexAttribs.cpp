/*
 * Copyright (C) 2013 Sergey Kosarevsky (sk@linderdaum.com)
 * Copyright (C) 2013 Viktor Latypov (vl@linderdaum.com)
 * Based on Linderdaum Engine http://www.linderdaum.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must display the names 'Sergey Kosarevsky' and
 *    'Viktor Latypov'in the credits of the application, if such credits exist.
 *    The authors of this work must be notified via email (sk@linderdaum.com) in 
 *    this case of redistribution.
 *
 * 3. Neither the name of copyright holders nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "VertexAttribs.h"

clVertexAttribs::clVertexAttribs()
	: FActiveVertexCount( 0 ),
	  FVertices( 0 ),
	  FTexCoords( 0 ),
	  FNormals( 0 ),
	  FColors( 0 ),
	  FCurrentTexCoords(),
	  FCurrentNormal(),
	  FCurrentColor( 1.0f, 1.0f, 1.0f, 1.0f ),
	  FStreams( L_VS_TOTAL_ATTRIBS )
{
}

clVertexAttribs::clVertexAttribs( size_t Vertices )
	: FActiveVertexCount( Vertices ),
	  FVertices( Vertices ),
	  FTexCoords( Vertices ),
	  FNormals( Vertices ),
	  FColors( Vertices ),
	  FCurrentTexCoords(),
	  FCurrentNormal(),
	  FCurrentColor( 1.0f, 1.0f, 1.0f, 1.0f ),
	  FStreams( L_VS_TOTAL_ATTRIBS )
{
}

const std::vector<const void*>& clVertexAttribs::EnumerateVertexStreams() const
{
	FStreams[ L_VS_VERTEX   ] = &FVertices[0];
	FStreams[ L_VS_TEXCOORD ] = &FTexCoords[0];
	FStreams[ L_VS_NORMAL   ] = &FNormals[0];
	FStreams[ L_VS_COLORS   ] = &FColors[0];

	return FStreams;
}

void clVertexAttribs::SetTexCoordV( const LVector2& V )
{
	FCurrentTexCoords = V;
}

void clVertexAttribs::SetNormalV( const LVector3& Vec )
{
	FCurrentNormal = Vec;
}

void clVertexAttribs::SetColorV( const LVector4& Vec )
{
	FCurrentColor = Vec;
}

void clVertexAttribs::Restart( size_t ReserveVertices )
{
	FCurrentColor     = LVector4( 1.0f, 1.0f, 1.0f, 1.0f );
	FCurrentNormal    = LVector3( 0, 0, 0 );
	FCurrentTexCoords = LVector2( 0, 0 );

	FActiveVertexCount = 0;

	FVertices.resize( ReserveVertices );
	FTexCoords.resize( ReserveVertices );
	FNormals.resize( ReserveVertices );
	FColors.resize( ReserveVertices );
}

void clVertexAttribs::EmitVertexV( const LVector3& Vec )
{
	FVertices[ FActiveVertexCount ] = Vec;
	FTexCoords[ FActiveVertexCount ] = FCurrentTexCoords;
	FNormals[ FActiveVertexCount ] = FCurrentNormal;
	FColors[ FActiveVertexCount ] = FCurrentColor;

	FActiveVertexCount++;
}
